/*
    Software License Agreement (BSD License)
    
    Copyright (c) 1997-2011, David Lindauer, (LADSoft).
    All rights reserved.
    
    Redistribution and use of this software in source and binary forms, 
    with or without modification, are permitted provided that the following 
    conditions are met:
    
    * Redistributions of source code must retain the above
      copyright notice, this list of conditions and the
      following disclaimer.
    
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the
      following disclaimer in the documentation and/or other
      materials provided with the distribution.
    
    * Neither the name of LADSoft nor the names of its
      contributors may be used to endorse or promote products
      derived from this software without specific prior
      written permission of LADSoft.
    
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
    PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER 
    OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
    OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
    OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
    ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "compiler.h"

extern int nextLabel;
extern int errorline;

#ifndef CPREPROCESSOR
extern ARCH_DEBUG *chosenDebugger;
extern FILE *listFile;
#endif
NAMESPACEVALUES *globalNameSpace, *localNameSpace;
HASHTABLE *labelSyms;

HASHTABLE *CreateHashTable(int size);

static LIST *usingDirectives;

#ifdef PARSER_ONLY
extern HASHTABLE *kwhash;
extern HASHTABLE *defsyms;
extern HASHTABLE *labelSyms;
extern HASHTABLE *ccHash;
void ccSetSymbol(SYMBOL *s);
#endif

void syminit(void)
{
    globalNameSpace = Alloc(sizeof(NAMESPACEVALUES));
    globalNameSpace->syms = CreateHashTable(GLOBALHASHSIZE);
    globalNameSpace->tags = CreateHashTable(GLOBALHASHSIZE);
    localNameSpace = Alloc(sizeof(NAMESPACEVALUES));
    usingDirectives = NULL;
}
HASHTABLE *CreateHashTable(int size)
{
    HASHTABLE *rv = Alloc(sizeof(HASHTABLE));
    rv->table = Alloc(sizeof(HASHREC *) * size);
    rv->size = size;
    return rv;
}
#ifndef CPREPROCESSOR
void AllocateLocalContext(BLOCKDATA *block, SYMBOL *sp)
{
    HASHTABLE *tn = CreateHashTable(1);
    STATEMENT *st;
    LIST *l;
    int label = nextLabel++;
    st = stmtNode(block, st_dbgblock);
    st->label = 1;
    if (block && cparams.prm_debug)
    {
        st = stmtNode(block, st_label);
        st->label = label;
        tn->blocknum = st->blocknum;
    }
    tn->next = localNameSpace->syms;
    localNameSpace->syms = tn;
    tn = CreateHashTable(1);
    if (block && cparams.prm_debug)
    {
        tn->blocknum = st->blocknum;
    }
    tn->next = localNameSpace->tags;
    localNameSpace->tags = tn;
    if (sp)
        localNameSpace->tags->blockLevel = sp->value.i++;
    
    l = Alloc(sizeof(LIST));
    l->data = localNameSpace->usingDirectives;
    l->next = usingDirectives;
    usingDirectives = l;
    
}
#ifdef PARSER_ONLY
void TagSyms(HASHTABLE *syms)
{
    int i;
    for (i=0; i < syms->size; i++)
    {
        HASHREC *hr = syms->table[i];
        while (hr)
        {
            SYMBOL *sp = (SYMBOL *)hr->p;
            sp->ccEndLine = errorline;
            hr = hr->next;
        }    
    }
}
#endif
void FreeLocalContext(BLOCKDATA *block, SYMBOL *sp)
{
    HASHTABLE *locals = localNameSpace->syms;
    HASHTABLE *tags = localNameSpace->tags;
    STATEMENT *st;
    int label = nextLabel++;
    if (block && cparams.prm_debug)
    {
        st = stmtNode(block, st_label);
        st->label = label;
    }
    checkUnused(localNameSpace->syms);
    if (sp && listFile)
    {
        if (localNameSpace->syms->table[0])
        {
            fprintf(listFile, "******** Local Symbols ********\n");
            list_table(sp->inlineFunc.syms,0);
            fprintf(listFile, "\n");
        }
        if (localNameSpace->tags->table[0])
        {
            fprintf(listFile,"******** Local Tags ********\n");
            list_table(sp->inlineFunc.tags, 0);
            fprintf(listFile, "\n");
        }
    }
    if (sp)
        sp->value.i--;

    destructBlock(block, localNameSpace->syms);    
    localNameSpace->syms = localNameSpace->syms->next;
    localNameSpace->tags = localNameSpace->tags->next;

    localNameSpace->usingDirectives = usingDirectives->data;
    usingDirectives = usingDirectives->next;

#ifdef PARSER_ONLY
    TagSyms(locals);
    TagSyms(tags);
#endif
    if (sp)
    {
        locals->next = sp->inlineFunc.syms;
        tags->next = sp->inlineFunc.tags;
        sp->inlineFunc.syms = locals;
        sp->inlineFunc.tags = tags;
    }
    st = stmtNode(block, st_dbgblock);
    st->label = 0;
}
#endif
/* SYMBOL tab hash function */
static HASHREC **GetHashLink(HASHTABLE *t, char *string)
{
    unsigned i;
    if ( t->size == 1)
        return &t->table[0];
    for (i = 0;  *string; string++)
        i = ((i << 7) + (i << 1) +i )  ^ *string;
    return &t->table[i % t->size];
}
/* Add a hash item to the table */
HASHREC *AddName(SYMBOL *item, HASHTABLE *table)
{
    HASHREC **p = GetHashLink(table, item->name);
    HASHREC *newRec;

    if (*p)
    {
        HASHREC *q =  *p,  *r =  *p;
        while (q)
        {
            r = q;
            if (!strcmp(r->p->name, item->name))
                return (r);
            q = q->next;
        }
        newRec = Alloc(sizeof(HASHREC));
        r->next = newRec;
        newRec->p = (struct _hrintern_ *)item;
    }
    else
    {
        newRec = Alloc(sizeof(HASHREC));
        *p = newRec;
        newRec->p = (struct _hrintern_ *)item;
    }
    return (0);
}
static HASHREC *AddOverloadName(SYMBOL *item, HASHTABLE *table)
{
    HASHREC **p = GetHashLink(table, item->decoratedName);
    HASHREC *newRec;

    if (*p)
    {
        HASHREC *q =  *p,  *r =  *p;
        while (q)
        {
            r = q;
            if (!strcmp(((SYMBOL *)r->p)->decoratedName, item->decoratedName))
                return (r);
            q = q->next;
        }
        newRec = Alloc(sizeof(HASHREC));
        r->next = newRec;
        newRec->p = (struct _hrintern_ *)item;
    }
    else
    {
        newRec = Alloc(sizeof(HASHREC));
        *p = newRec;
        newRec->p = (struct _hrintern_ *)item;
    }
    return (0);
}

/*
 * Find something in the hash table
 */
HASHREC **LookupName(char *name, HASHTABLE *table)
{
    HASHREC **p = GetHashLink(table, name);

    while (*p)
    {
        if (!strcmp((*p)->p->name, name))
            return p;
        p =  (HASHREC **)*p;
    }
    return (0);
}
SYMBOL *search(char *name, HASHTABLE *table)
{
    while (table)
    {
        HASHREC **p = LookupName(name, table);
        if (p)
            return (SYMBOL *)(*p)->p;
        table = table->next;
    }
    return 0;
}
SYMBOL *searchOverloads(char *name, HASHTABLE *table)
{
    HASHREC **p = GetHashLink(table, name);
    int pl = strlen(name);
    while (*p)
    {
        char *q = ((SYMBOL *)(*p)->p)->decoratedName;
        int ql = strlen(q);
        if (pl <= ql)
        {
            if (!strcmp(q + ql - pl, name))
                return (SYMBOL *)(*p)->p;
        }
        p =  (HASHREC **)*p;
    }
    return (0);
}
SYMBOL *gsearch(char *name)
{
    SYMBOL *sp = search(name, localNameSpace->syms);
    if (sp)
        return sp;
    return search(name, globalNameSpace->syms);
}
SYMBOL *tsearch(char *name)
{
    SYMBOL *sp = search(name, localNameSpace->tags);
    if (sp)
        return sp;
    return search(name, globalNameSpace->tags);
}
void insert(SYMBOL *in, HASHTABLE *table)
{
#ifdef PARSER_ONLY
    if (table != defsyms && table != kwhash && table != labelSyms && table != ccHash)
        ccSetSymbol(in);
#endif
    if (cparams.prm_extwarning)
        if (in->storage_class == sc_parameter || in->storage_class == sc_auto ||
            in->storage_class == sc_register)
        {
            SYMBOL *sp;
            if ((sp = gsearch(in->name)) != NULL)
                preverror(ERR_VARIABLE_OBSCURES_VARIABLE_AT_HIGHER_SCOPE, in->name, 
                         sp->declfile, sp->declline);
        }
#if defined (PARSER_ONLY)
    if (AddName(in, table) && table != ccHash)
#else
    if (AddName(in, table))
#endif
    {
#if defined(CPREPROCESSOR) || defined(PARSER_ONLY)
        pperrorstr(ERR_DUPLICATE_IDENTIFIER, in->name);
#else
        preverrorsym(ERR_DUPLICATE_IDENTIFIER, in, in->declfile, in->declline);
#endif
    }
}

void insertOverload(SYMBOL *in, HASHTABLE *table)
{
    if (cparams.prm_extwarning)
        if (in->storage_class == sc_parameter || in->storage_class == sc_auto ||
            in->storage_class == sc_register)
        {
            SYMBOL *sp;
            if ((sp = gsearch(in->name)) != NULL)
                preverror(ERR_VARIABLE_OBSCURES_VARIABLE_AT_HIGHER_SCOPE, in->name, 
                         sp->declfile, sp->declline);
        }
    if (AddOverloadName(in, table))
    {
#ifdef CPREPROCESSOR
        pperrorstr(ERR_DUPLICATE_IDENTIFIER, in->name);
#else
    preverrorsym(ERR_DUPLICATE_IDENTIFIER, in, in->declfile, in->declline);
#endif
    }
}


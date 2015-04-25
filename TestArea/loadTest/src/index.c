
#include <stdio.h>
#include <malloc.h>
#include "assert.h"
#include "index.h"
#include "card.h"


/**
 * ����һ��ֻ��һ���ڵ���µ�����
 */
struct Node * RTreeNewIndex()
{
	struct Node *x;			/* һ���ڵ� */
	x = RTreeNewNode();		/* �������Node */
	x->level = 0;			/* ��Ϊֻ��һ���ڵ㣬��ô����Ҷ�ӣ���ôlevel=0 */
	return x;				/* ��������µ������ڵ� */
}

/**
 * ����Ŀ���������λ��(����˵�漰����Щ���ݾ��ΰ�)
 *
 * ���������ڵ� + Ŀ����� + �ص����� + ���Ӳ���
 *
 * �����ҵ������ݾ��εĸ���
 */
int RTreeSearch(struct Node *N, struct Rect *R, SearchHitCallback shcb, void* cbarg)
{
	register struct Node *n = N;
	register struct Rect *r = R;
	register int hitCount = 0;
	register int i;
	
	assert(n);
	assert(n->level >= 0);
	assert(r);

	/**
	 * ��n��һ�������ĸ�
	 */
	if (n->level > 0)
	{
		/**
		 * �����еĽڵ���б���
		 */
		for (i=0; i<NODECARD; i++)
			if (n->branch[i].child &&				/* �ж�����Ӿ��δ��� && �ص��� ==> �ҵ�һ�������"�����" */
			    RTreeOverlap(r,&n->branch[i].rect))	/* �ж����������Ƿ��ص�
				                                     * �������������� + ����һ����֧���� 
													 */
			{
				/**
				 * ����������еݹ��жϣ�ֱ���ҵ��������ݾ���
				 */
				hitCount += RTreeSearch(n->branch[i].child, R, shcb, cbarg);
			}
	}
	/**
	 * ��n��һ��Ҷ�ӽڵ�( �������ݾ����ˣ���������Ҫ�����յĽ���� )
	 */
	else
	{
		for (i=0; i<LEAFCARD; i++)
			if (n->branch[i].child &&				/* ������� && �ص��� ==> �ҵ�һ�������"���ݾ���" */
			    RTreeOverlap(r,&n->branch[i].rect))
			{
				hitCount++;							/* count++ */
			
				/**
				 * ���������Ƿ��Լ��������Լ��Ļص�����
				 */
				if(shcb)
					if( ! shcb((int)n->branch[i].child, cbarg))	/* �ȴ�������ص����� */
						return hitCount;
			}
	}
	
	return hitCount;
}

/**
 * ʵ��ִ�У�����һ�����ݾ��ε������ṹ��
 * ��һ���ݹ��½���
 * ����1����root�����ˣ�0����û�з���
 * ע����������ݾ��Σ����ݾ��ε�id���������µĽڵ㣻�㼶
 */
static int RTreeInsertRect2(struct Rect *r,
		int tid, struct Node *n, struct Node **new_node, int level)
{
	register int i;
	struct Branch b;
	struct Node *n2;

	assert(r && n && new_node);
	assert(level >= 0 && level <= n->level);

	/**
	 * ע�����������֮��n��������
	 */
	
	/**
	 * û�дﵽ�Լ��Ĳ㼶���ʹ���( ��һ���ݹ��½��� )
	 */
	if (n->level > level)
	{
		i = RTreePickBranch(r, n);	/* �ҵ�һ���ܹ������Լ���������������ٵ��Ǹ�rect��
		                             * ���������ݾ��κ͸� 
		                             */
		
		/**
		 * ������еݹ鴦���Ӿ���
		 * ֻ�е��Ǹ���ν�ĸ�(n->branch[i].child)û�з�֧��ʱ��
		 * ��ô˵�������ݾ��Σ���ô�����յĹ���
		 */
		if (!RTreeInsertRect2(r, tid, n->branch[i].child, &n2, level))
		{
			// ����û�з��ѣ�
			//
			n->branch[i].rect =
				RTreeCombineRect(r,&(n->branch[i].rect));	/* ���������κϲ� */
			return 0;
		}
		else// ���ӷ����ˣ�
		{
			n->branch[i].rect = RTreeNodeCover(n->branch[i].child);
			b.child = n2;
			b.rect = RTreeNodeCover(n2);
			return RTreeAddBranch(&b, n, new_node);
		}
	}
	else if (n->level == level)			/* �ﵽ�˿��Բ���Ĳ㼶���Ͳ��룬ע���Ҫ��ʱ����з��ѣ� */
	{
		b.rect = *r;					/* ����һ���µķ�֧�����ξ����µ����ݾ��� */
		b.child = (struct Node *) tid;	/* ��ν��B�ĺ��ӣ���ʵ���Լ���id */
		/* child field of leaves contains tid of data record */
		return RTreeAddBranch(&b, n, new_node);	/* ���� */
	}
	else
	{
		assert (FALSE);	/* ��һ���ǲ�������ͨ���ģ� */
		return 0;
	}
}

/**
 * ����һ�����ε������ṹ��
 *
 * ע���������Ҫ����Ϊ���ж��Ƿ���Ҫ���ѽڵ�
 *
 * ע�ⷵ��ֵ��1����������ˣ�0����û�з���
 *
 * level��0����Ҷ�ӣ����������Ҷ�ӽڵ�
 *
 * �������RTreeInsertRect2�еݹ鴦��
 */
int RTreeInsertRect(struct Rect *R, int Tid, struct Node **Root, int Level)
{
	register struct Rect *r = R;				/* �������r */
	register int tid = Tid;						/* ����������ݾ��ε�id */
	register struct Node **root = Root;			/* ���� */
	register int level = Level;					/* ���ݾ������ڵ�level��һ�����ݾ��ζ���0��Ҷ�� */

	register int i;
	register struct Node *newroot;				/* ���ܵ��µ�root�����ѵ��� */
	struct Node *newnode;						/* �µĽڵ� */
	struct Branch b;							/* ��֧ */
	int result;									/* ���ؽ����1����������ˣ�0����û�з��� */

	/**
	 * ���Ϸ���
	 */
	assert(r && root);
	assert(level >= 0 && level <= (*root)->level);
	for (i=0; i<NUMDIMS; i++)
	{
		assert(r->boundary[i] <= r->boundary[NUMDIMS+i]);	/* ���겻���� */
	}

	/**
	 * ����ʹ��RTreeInsertRect2���в���������Σ����ж��Ƿ����
	 *
	 * ��������ˣ���ô
	 *
	 * ע����������ݾ��Σ����ݾ��ε�id���������µĽڵ㣻�㼶
	 */
	if (RTreeInsertRect2(r, tid, *root, &newnode, level))  /* 
		                                                    * ����������ˣ�ע��ͬʱһ���µķ�֧
															* newnode���أ�����һ����֧����֮ǰ��
															* root�����Բ���Ҫ���أ�ֻ�����ݱ仯�˶���
															*/
	{
		newroot = RTreeNewNode();			/* �������µĽڵ�root��newnode��Ҫ��һ���µ�newroot���� */
		newroot->level = (*root)->level + 1;/* ��θ�һ������ */
		
		/**
		 * �����֧һ
		 */
		b.rect = RTreeNodeCover(*root);		/* b.rect�ǰ���root������С���εĴ���� */	
		b.child = *root;					/* b�ĺ��Ӿ���root */
		RTreeAddBranch(&b, newroot, NULL);	/* Ȼ����newroot��������һ���µķ�֧b(Ҳ����֮ǰ��root) */
		
		b.rect = RTreeNodeCover(newnode);	/* Ȼ��b��rect��ֵΪ�ڶ������ѵ��µĽڵ� 
											 * b.rect�ǰ���newnode������С���εĴ����
		                                     */
		/**
		 * �����֧��
		 */
		b.child = newnode;					/* b�ĺ��Ӿ���node */
		RTreeAddBranch(&b, newroot, NULL);	/* Ȼ����newroot��������һ���µķ�֧newnode */

		/**
		 * ע��rootָ����Ҫ�滻��Ŷ~~~ ^_^
		 */
		*root = newroot;
		result = 1;							/* ����1����ڵ������ */
	}
	else
	{
		result = 0;
	}

	return result;
}




// Allocate space for a node in the list used in DeletRect to
// store Nodes that are too empty.
//
static struct ListNode * RTreeNewListNode()
{
	return (struct ListNode *) malloc(sizeof(struct ListNode));
	//return new ListNode;
}


static void RTreeFreeListNode(struct ListNode *p)
{
	free(p);
	//delete(p);
}



// Add a node to the reinsertion list.  All its branches will later
// be reinserted into the index structure.
//
static void RTreeReInsert(struct Node *n, struct ListNode **ee)
{
	register struct ListNode *l;

	l = RTreeNewListNode();
	l->node = n;
	l->next = *ee;
	*ee = l;
}


// Delete a rectangle from non-root part of an index structure.
// Called by RTreeDeleteRect.  Descends tree recursively,
// merges branches on the way back up.
// Returns 1 if record not found, 0 if success.
//
static int
RTreeDeleteRect2(struct Rect *R, int Tid, struct Node *N, struct ListNode **Ee)
{
	register struct Rect *r = R;
	register int tid = Tid;
	register struct Node *n = N;
	register struct ListNode **ee = Ee;
	register int i;

	assert(r && n && ee);
	assert(tid >= 0);
	assert(n->level >= 0);

	if (n->level > 0)  // not a leaf node
	{
	    for (i = 0; i < NODECARD; i++)
	    {
		if (n->branch[i].child && RTreeOverlap(r, &(n->branch[i].rect)))
		{
			if (!RTreeDeleteRect2(r, tid, n->branch[i].child, ee))
			{
				if (n->branch[i].child->count >= MinNodeFill)
					n->branch[i].rect = RTreeNodeCover(
						n->branch[i].child);
				else
				{
					// not enough entries in child,
					// eliminate child node
					//
					RTreeReInsert(n->branch[i].child, ee);
					RTreeDisconnectBranch(n, i);
				}
				return 0;
			}
		}
	    }
	    return 1;
	}
	else  // a leaf node
	{
		for (i = 0; i < LEAFCARD; i++)
		{
			if (n->branch[i].child &&
			    n->branch[i].child == (struct Node *) tid)
			{
				RTreeDisconnectBranch(n, i);
				return 0;
			}
		}
		return 1;
	}
}



// Delete a data rectangle from an index structure.
// Pass in a pointer to a Rect, the tid of the record, ptr to ptr to root node.
// Returns 1 if record not found, 0 if success.
// RTreeDeleteRect provides for eliminating the root.
//
int RTreeDeleteRect(struct Rect *R, int Tid, struct Node**Nn)
{
	register struct Rect *r = R;
	register int tid = Tid;
	register struct Node **nn = Nn;
	register int i;
	register struct Node *tmp_nptr;
	struct ListNode *reInsertList = NULL;
	register struct ListNode *e;

	assert(r && nn);
	assert(*nn);
	assert(tid >= 0);

	if (!RTreeDeleteRect2(r, tid, *nn, &reInsertList))
	{
		/* found and deleted a data item */

		/* reinsert any branches from eliminated nodes */
		while (reInsertList)
		{
			tmp_nptr = reInsertList->node;
			for (i = 0; i < MAXKIDS(tmp_nptr); i++)
			{
				if (tmp_nptr->branch[i].child)
				{
					RTreeInsertRect(
						&(tmp_nptr->branch[i].rect),
						(int)tmp_nptr->branch[i].child,
						nn,
						tmp_nptr->level);
				}
			}
			e = reInsertList;
			reInsertList = reInsertList->next;
			RTreeFreeNode(e->node);
			RTreeFreeListNode(e);
		}
		
		/* check for redundant root (not leaf, 1 child) and eliminate
		*/
		if ((*nn)->count == 1 && (*nn)->level > 0)
		{
			for (i = 0; i < NODECARD; i++)
			{
				tmp_nptr = (*nn)->branch[i].child;
				if(tmp_nptr)
					break;
			}
			assert(tmp_nptr);
			RTreeFreeNode(*nn);
			*nn = tmp_nptr;
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

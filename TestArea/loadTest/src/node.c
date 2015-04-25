
#include <stdio.h>
#include <malloc.h>
#include "assert.h"
#include "index.h"
#include "card.h"


/**
 * ��ʼ��һ���ڵ�����еķ�֧
 */
static void RTreeInitBranch(struct Branch *b)
{
	RTreeInitRect(&(b->rect));				/* ʵ�ʾ��ǳ�ʼ��������� */
	b->child = NULL;						/* û�к��� */
}


/**
 * ��ʼ������һ���ڵ�
 */
void RTreeInitNode(struct Node *N)
{
	register struct Node *n = N;
	register int i;
	n->count = 0;							/* ��֧��=0 */
	n->level = -1;							
	for (i = 0; i < MAXCARD; i++)			/* �����ʼ��ÿһ����֧ */
	{
		RTreeInitBranch(&(n->branch[i]));	/* ��ʼ�� */
	}
}



/**
 * ����һ���µĽڵ㣬����ʼ�����з�֧Ϊ��
 */
struct Node * RTreeNewNode()
{
	register struct Node *n;

	//n = new Node;
	n = (struct Node*)malloc(sizeof(struct Node));	/* ����ռ� */
	assert(n);										/* ��� */
	RTreeInitNode(n);								/* ��ʼ��R���Ľڵ� */
	return n;
}

/**
 * �ͷ�һ���ڵ�
 */
void RTreeFreeNode(struct Node *p)
{
	assert(p);
	//delete p;
	free(p);										/* just free */
}



static void RTreePrintBranch(struct Branch *b, int depth)
{
	RTreePrintRect(&(b->rect), depth);
	RTreePrintNode(b->child, depth);
}


extern void RTreeTabIn(int depth)
{
	int i;
	for(i=0; i<depth; i++)
		putchar('\t');
}


// Print out the data in a node.
//
void RTreePrintNode(struct Node *n, int depth)
{
	int i;
	assert(n);

	RTreeTabIn(depth);
	printf("node");
	if (n->level == 0)
		printf(" LEAF");
	else if (n->level > 0)
		printf(" NONLEAF");
	else
		printf(" TYPE=?");
	printf("  level=%d  count=%d  address=%o\n", n->level, n->count, n);

	for (i=0; i<n->count; i++)
	{
		if(n->level == 0) {
			// RTreeTabIn(depth);
			// printf("\t%d: data = %d\n", i, n->branch[i].child);
		}
		else {
			RTreeTabIn(depth);
			printf("branch %d\n", i);
			RTreePrintBranch(&n->branch[i], depth+1);
		}
	}
}

/**
 * ���ذ������еľ��εĴ����
 */
struct Rect RTreeNodeCover(struct Node *N)
{
	register struct Node *n = N;
	register int i, first_time=1;
	struct Rect r;
	assert(n);

	RTreeInitRect(&r);					/* ��ʼ������r */

	/**
	 * ��������еķ�֧���д���
	 */
	for (i = 0; i < MAXKIDS(n); i++)
		if (n->branch[i].child)			/* �����֧�����к��ӵ� */
		{
			if (first_time)				/* ��һ�ζ�r���� */
			{
				r = n->branch[i].rect;	/* r���ڵ�һ����֧��rect */
				first_time = 0;
			}
			else
				r = RTreeCombineRect(&r, &(n->branch[i].rect));	/* ����ܹ��������еľ��εĴ���� */
		}
	return r;
}



/**
 * ѡ��һ����Ҫ������������ķ�֧��װ��������ݾ���( �����ٵ������� )
 * ���������������һ�����������ӵķ�֧����ô��ѡ��֮ǰ��С���Ǹ�
 *
 * ע����������ݾ��� + ��
 */
int RTreePickBranch(struct Rect *R, struct Node *N)
{
	register struct Rect *r = R;	/* ���ݾ��� */
	register struct Node *n = N;	/* �� */
	register struct Rect *rr;
	register int i, first_time=1;
	RectReal increase, bestIncr = (RectReal)-1, area, bestArea;
	int best;
	struct Rect tmp_rect;
	assert(r && n);
	
	/**
	 * ����n��ÿһ����֧����
	 * Ҫʱ��ע�����ǵ�Ŀ����ʲô���ҵ�һ������С�ĺϷ��ľ���
	 *
	 */
	for (i=0; i<MAXKIDS(n); i++)
	{
		if (n->branch[i].child)					/* ���һ����֧�к��Ӵ��� */
		{	
			rr = &n->branch[i].rect;			/* ��÷�֧�ľ��� */
			
			area = RTreeRectSphericalVolume(rr);/* �õ��������� */

			tmp_rect = RTreeCombineRect(r, rr);	/* ����һ���µľ����ܹ���ס������������ľ���
			                                     * ע�����������rect + ��֧rect 
			                                     */

			increase = RTreeRectSphericalVolume(&tmp_rect) - area;	/* �������ν��֮���γ�һ��
																	 * ��ľ��Ρ���ô������������
																	 * �����˶����أ�
																	 * ����������Ҫ��������ٵ����������
			                                                         */
			/**
			 * �������ɸѡ�����������С���Ǹ�( first_time��һ��������� )
			 */
			if (increase < bestIncr || first_time)
			{
				best = i;
				bestArea = area;
				bestIncr = increase;
				first_time = 0;
			}
			else if (increase == bestIncr && area < bestArea)	/* �����ȣ���ôѡ�����С�ģ�Ϊ�˱�֤��С������^_^ */
			{
				best = i;
				bestArea = area;
				bestIncr = increase;
			}
		}
	}

	return best;
}



/**
 * ����һ����֧���ڵ���ȥ( �����Ҫ�Ļ���Ҫ��������ڵ� )
 * ������
 *     �µķ�֧B�������֧�ĸ��ڵ�N���µĽڵ�New_node
 *
 * ����0��û�з���( �ϵĽڵ㱻���� )
 * ����1��������  ( new_node������ ) �ֳ������ڵ�
 */
int RTreeAddBranch(struct Branch *B, struct Node *N, struct Node **New_node)
{
	register struct Branch *b = B;
	register struct Node *n = N;
	register struct Node **new_node = New_node;
	register int i;
	
	assert(b);
	assert(n);
	
	if (n->count < MAXKIDS(n))				/* ��û�б�Ҫ���ѣ� */
	{
		for (i = 0; i < MAXKIDS(n); i++)	/* ��Ҫ�ҵ�һ���յķ�֧ */
		{
			if (n->branch[i].child == NULL)	/* �������ĺ���ΪNULL:����Ҷ�ӽڵ� */
			{
				n->branch[i] = *b;			/* ��֧��ֵ */
				n->count++;					/* n�ķ�֧�ֶ�һ�� */
				break;
			}
		}
		return 0;
	}
	else
	{
		assert(new_node);
		RTreeSplitNode(n, b, new_node);		/* ��Ҫ���з��ѣ� 
											 * ������������֧���µĽڵ�
											 * ע�����շ�����һ���µ�node( ����һ����֧����֮ǰ��n )
		                                     */
		return 1;
	}
}



// Disconnect a dependent node.
//
void RTreeDisconnectBranch(struct Node *n, int i)
{
	assert(n && i>=0 && i<MAXKIDS(n));
	assert(n->branch[i].child);

	RTreeInitBranch(&(n->branch[i]));
	n->count--;
}

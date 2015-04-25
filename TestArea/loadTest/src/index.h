#ifndef _INDEX_
#define _INDEX_

#define PGSIZE	512		/* ������һ������ҳ�Ĵ�С */
#define NUMDIMS	2		/* number of dimensions��ά���������Ƕ�ά�ľ��� */
#define NDEBUG

typedef float RectReal;	/* ������εĵ��������float */


/*-----------------------------------------------------------------------------
| ȫ�ֶ���
-----------------------------------------------------------------------------*/

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define NUMSIDES 2*NUMDIMS		/* ���αߵ�����=4����ʵ����������º���������������� */

/**
 * ���涨�����
 */
struct Rect
{
	RectReal boundary[NUMSIDES]; /* �߽磺xmin,ymin,...,xmax,ymax,... */
};

struct Node;

/**
 * ���涨���֧
 */
struct Branch
{
	struct Rect rect;			/* ���ڵľ��� */
	struct Node *child;			/* ����ָ�� */
};

/**
 * һ��page���ܱ����Branch�����ĸ���
 */
#define MAXCARD (int)((PGSIZE-(2*sizeof(int))) / sizeof(struct Branch))

/**
 * ���涨��ڵ�
 */
struct Node
{
	int count;						/* �����ķ�֧�ĸ��� */
	int level;						/* 0 is leaf, others positive */
	struct Branch branch[MAXCARD];	/* ��֧���� */
};

/**
 * �ڵ������������ã���ɾ����ʱ��
 */
struct ListNode
{
	struct ListNode *next;			/* ��һ���ڵ� */
	struct Node *node;				/* ��ǰ�ڵ� */
};


typedef int (*SearchHitCallback)(int id, void* arg);


extern int RTreeSearch(struct Node*, struct Rect*, SearchHitCallback, void*);
extern int RTreeInsertRect(struct Rect*, int, struct Node**, int depth);
extern int RTreeDeleteRect(struct Rect*, int, struct Node**);
extern struct Node * RTreeNewIndex();
extern struct Node * RTreeNewNode();
extern void RTreeInitNode(struct Node*);
extern void RTreeFreeNode(struct Node *);
extern void RTreePrintNode(struct Node *, int);
extern void RTreeTabIn(int);
extern struct Rect RTreeNodeCover(struct Node *);
extern void RTreeInitRect(struct Rect*);
extern struct Rect RTreeNullRect();
extern RectReal RTreeRectArea(struct Rect*);
extern RectReal RTreeRectSphericalVolume(struct Rect *R);
extern RectReal RTreeRectVolume(struct Rect *R);
extern struct Rect RTreeCombineRect(struct Rect*, struct Rect*);
extern int RTreeOverlap(struct Rect*, struct Rect*);
extern void RTreePrintRect(struct Rect*, int);
extern int RTreeAddBranch(struct Branch *, struct Node *, struct Node **);
extern int RTreePickBranch(struct Rect *, struct Node *);
extern void RTreeDisconnectBranch(struct Node *, int);
extern void RTreeSplitNode(struct Node*, struct Branch*, struct Node**);

extern int RTreeSetNodeMax(int);
extern int RTreeSetLeafMax(int);
extern int RTreeGetNodeMax();
extern int RTreeGetLeafMax();

#endif /* _INDEX_ */

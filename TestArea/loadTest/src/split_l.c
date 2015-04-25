
#include <stdio.h>
#include "assert.h"
#include "index.h"
#include "card.h"
#include "split_l.h"

/**
 * �õ�
 * �������� + ��֧
 */
static void RTreeGetBranches(struct Node *N, struct Branch *B)
{
	register struct Node *n = N;
	register struct Branch *b = B;
	register int i;

	assert(n);
	assert(b);

	for (i=0; i<MAXKIDS(n); i++)
	{
		assert(n->branch[i].child);		/* ÿһ����֧�����������ݵĲ��Ǻ���ģ� */
		BranchBuf[i] = n->branch[i];	/* ��֧������ */
	}

	BranchBuf[MAXKIDS(n)] = *b;			/* ���һ���ռ����Ҫ�µ�branch */
	BranchCount = MAXKIDS(n) + 1;		/* ��֧���� = MAXKIDS(n) + 1 */

	/**
	 * ������ʵ�Ǽ����ܹ���������Щ���ΰ��������Ĵ�ľ���
	 */
	CoverSplit = BranchBuf[0].rect;		/* ��ʼ��һ��rect�����Ǿ�����ȥ~ */
	
	for (i=1; i<MAXKIDS(n)+1; i++)		/* ��ÿһ���Ӿ��ν��д��� */
	{
		CoverSplit = RTreeCombineRect(&CoverSplit, &BranchBuf[i].rect);	/* �õ������ */
	}

	RTreeInitNode(n);					/* ����n���� */
}

/**
 * ��ʼ�������Ľṹ��
 *
 * ���������� + rect�ĸ��� + һ����Ҷ�ӽڵ����ӵ�е����ٵĽڵ���
 */
static void RTreeInitPVars(struct PartitionVars *P, int maxrects, int minfill)
{
	register struct PartitionVars *p = P;
	register int i;
	assert(p);

	p->count[0] = p->count[1] = 0;	/* ���º�����������count����0 */
	p->total = maxrects;			/* �ܵ�rect������ */
	p->minfill = minfill;			/* ÿ����Ҷ�ӽڵ�Ŀ���ӵ�е����ٵĽڵ��� */

	for (i=0; i<maxrects; i++)		/* ����ÿ��rect��˵ */
	{
		p->taken[i] = FALSE;		/* ��ʼ����û�б����䵽��һ������ */
		p->partition[i] = -1;		/* ��Ȼ�����Լ��ķ���Ҳ��û��Ŷ��id����-1 */
	}
}

/**
 * ��һ��rect���뵽group���id�ķ�����ȥ
 *
 * ������rect��BranchBuf�е�λ�� + ����id(0����1) + �����ṹ
 */
static void RTreeClassify(int i, int group, struct PartitionVars *p)
{
	assert(p);
	assert(!p->taken[i]);

	p->partition[i] = group;				/* �������id */
	p->taken[i] = TRUE;						/* ˵���������� */

	if (p->count[group] == 0)				/* ����ǵ�һ�����Σ���ô����Ҫ����ΰ������� */
		p->cover[group] = BranchBuf[i].rect;/* ���� */
	else									/* 1�ŷ��� */
		p->cover[group] = RTreeCombineRect(&BranchBuf[i].rect,
					&p->cover[group]);		/* ����ΰ������� */

	p->area[group] = RTreeRectSphericalVolume(&p->cover[group]);	/* ���㵱ǰ���ε��������� */
	p->count[group]++;						/* count++ */
}

/**
 * �����������зֱ��ҵ�����rect��Ϊ���������ĵ�һ������
 *
 * ����ԭ���������������ص�����||������Զ��
 * 
 * ��ʵ�㷨��easy�������ҵ����½�����rect �� ���Ͻ���С��rect����ô����������֮��ľ���������!
 * �Լ���ͼ������
 */
static void RTreePickSeeds(struct PartitionVars *P)
{
	register struct PartitionVars *p = P;			/* ���� */
	register int i, dim, high;
	register struct Rect *r, *rlow, *rhigh;
	register float w, separation, bestSep;
	RectReal width[NUMDIMS];
	int leastUpper[NUMDIMS], greatestLower[NUMDIMS];
	int seed0, seed1;
	assert(p);
	
	/**
	 * greatestLower : �������½��Ǹ�������x����y��ֵ��rect��BranchBuf�е�λ��idx
	 * leastUpper	 : �������Ͻ��Ǹ�����С��x����y��ֵ��rect��BranchBuf�е�λ��idx
	 *
	 * ��ΪҪ�������Σ���ôx��y��������
	 */
	
	for (dim=0; dim<NUMDIMS; dim++)
	{
		high = dim + NUMDIMS;

		/* find the rectangles farthest out in each direction
		 * along this dimens */
		
		greatestLower[dim] = leastUpper[dim] = 0;
		
		/**
		 * ����������е�rect���д���
		 * 
		 * �ȶ�x���д����ٶ�y���д���
		 */
		for (i=1; i<NODECARD+1; i++)
		{
			r = &BranchBuf[i].rect;	/* ȡһ������ */

			if (r->boundary[dim] >	/* �õ�һ�������ֵ */
			    BranchBuf[greatestLower[dim]].rect.boundary[dim])
			{
				greatestLower[dim] = i;
			}

			if (r->boundary[high] <	/* �õ�һ����С��ֵ */
			    BranchBuf[leastUpper[dim]].rect.boundary[high])
			{
				leastUpper[dim] = i;
			}
		}

		/* find width of the whole collection along this dimension */
		/**
		 * ����Ǹ������ε�x��Ⱥ�y���( ��Χ )
		 */
		width[dim] = CoverSplit.boundary[high] -
			     CoverSplit.boundary[dim];
	}
	
	/**
	 * ������Ҫ�ҵ���õ�������������ʼ���ľ���
	 */
	for (dim=0; dim<NUMDIMS; dim++)
	{
		high = dim + NUMDIMS;

		assert(width[dim] >= 0);
		
		/**
		 * ���x // y�Ŀ��
		 */
		if (width[dim] == 0)	
			w = (RectReal)1;
		else
			w = width[dim];
		
		rlow = &BranchBuf[leastUpper[dim]].rect;		/* ���Ͻ�x // y��С��rect */
		rhigh = &BranchBuf[greatestLower[dim]].rect;	/* ���½�x // y����rect */

		if (dim == 0)									/* ����x */
		{
			seed0 = leastUpper[0];						/* ��һ������ */
			seed1 = greatestLower[0];					/* �ڶ������� */
			
			separation = bestSep =						/* ��÷������ */
				(rhigh->boundary[0] -
				 rlow->boundary[NUMDIMS]) / w;
		}	
		else											/* ����y */
		{
			separation =								/* ��÷������ */
				(rhigh->boundary[dim] -
				rlow->boundary[dim+NUMDIMS]) / w;

			if (separation > bestSep)					/* ��������С����ô���ã� */
			{
				seed0 = leastUpper[dim];
				seed1 = greatestLower[dim];
				bestSep = separation;
			}
		}
	}

	if (seed0 != seed1)					/* �������β���ͬһ��rect��OK�� */
	{	
		RTreeClassify(seed0, 0, p);		/* ����0����һ������seed0 */
		RTreeClassify(seed1, 1, p);		/* ����1����һ������seed1 */
	}
}

/**
 * ��û�м��������rects���������ÿ�δ���һ��rect
 *
 * ���������ƽ�֣���ô������һ�����ԣ�
 *
 * 1)�����һ�����Ѿ��ﵽmaxnum(ָ����������һ������Ҫ����minfill����)�ˣ���ô��r�ŵ���һ����
 * 2)����r�ŵ���ʹ�����ſռ���С���Ǹ�����
 * 3)�����2)��ƽ�֣���ô�ŵ�����ռ��С������^_^
 * 4)����r�ŵ�Ԫ���ٵ�����
 * 5)�������~
 */
static void RTreePigeonhole(struct PartitionVars *P)
{
	register struct PartitionVars *p = P;
	struct Rect newCover[2];
	register int i, group;
	RectReal newArea[2], increase[2];
	
	/**
	 * �����������Ĺ�����д���ÿһ��rect
	 */
	for (i=0; i<NODECARD+1; i++)
	{
		/**
		 * �����û�зŵ�������ȥ
		 */
		if (!p->taken[i])
		{
			/**
			 * ����һ��
			 * ���һ����������ˣ���ô�ŵ���һ��������ȥ
			 */
			if (p->count[0] >= p->total - p->minfill)	/* ��һ���������ٷ�minfill�� */
			{
				RTreeClassify(i, 1, p);					/* 0�����ˣ��ŵ�1���� */
				continue;
			}
			else if (p->count[1] >= p->total - p->minfill)
			{
				RTreeClassify(i, 0, p);					/* 1�����ˣ��ŵ�0���� */
				continue;
			}
				
			/**
			 * �������
			 *  �����չ��С���Ǹ�����
			 */

			/* ��Ԥ��rect�ŵ����������У���÷ֱ����ӵĿռ�Ĵ�С�� */
			for (group=0; group<2; group++)
			{
				if (p->count[group]>0)								/* ���ǵ�һ��rect */
					newCover[group] = RTreeCombineRect(
						&BranchBuf[i].rect,
						&p->cover[group]);	
				else												/* �ǵ�һ��rect */
					newCover[group] = BranchBuf[i].rect;

				newArea[group] = RTreeRectSphericalVolume(			/* ����µľ��ε��������� */
							&newCover[group]);

				increase[group] = newArea[group]-p->area[group];	/* ���� */
			}

			/* ������бȽϣ���ø�С����չ��һ�� */
			if (increase[0] < increase[1])
				RTreeClassify(i, 0, p);
			else if (increase[1] < increase[0])
				RTreeClassify(i, 1, p);
			
			/**
			 * ��������
			 * ��������������ȣ���ô��Ԫ�طŵ����С�ľ�����
			 */
			else if (p->area[0] < p->area[1])
				RTreeClassify(i, 0, p);
			else if (p->area[1] < p->area[0])
				RTreeClassify(i, 1, p);

			/**
			 * �����ģ�
			 * �����Ҳ��ȣ���ô�ŵ�Ԫ�رȽ��ٵķ�����
			 */
			else if (p->count[0] < p->count[1])
				RTreeClassify(i, 0, p);
			else
				RTreeClassify(i, 1, p);
		}
	}

	assert(p->count[0] + p->count[1] == NODECARD + 1);
}

/**
 * ���ַ���:�������ǽ�������rect���ѳ������µĴ��rect( ������������ )
 * ����������p + ���ٵ�ӵ�нڵ���
 */
static void RTreeMethodZero(struct PartitionVars *p, int minfill)
{
	RTreeInitPVars(p, BranchCount, minfill);	/* ��ʼ�������������ṹ */
	RTreePickSeeds(p);							/* �ֱ��ҵ����������������һ��rect�������� */
	RTreePigeonhole(p);							/* �����е�rect��������� */
}

/**
 * ��buf�е���������������������֧��ȥ
 *
 * ������N����һ���µĽڵ�
 *       Q���ڶ����µĽڵ�  ( �����ڵ�����ԭʼ��N���ѵõ� )
 *       P��������Ϣ
 */
static void RTreeLoadNodes(struct Node *N, struct Node *Q,
			struct PartitionVars *P)
{
	register struct Node *n = N, *q = Q;
	register struct PartitionVars *p = P;
	register int i;
	assert(n);
	assert(q);
	assert(p);

	/**
	 * ɨ�����еĵ㣬Ȼ������Լ���branch
	 */
	for (i=0; i<NODECARD+1; i++)
	{	
		if (p->partition[i] == 0)					/* ��һ���µĽڵ�(����) */
			RTreeAddBranch(&BranchBuf[i], n, NULL);
		else if (p->partition[i] == 1)				/* �ڶ����µĽڵ�(����) */
			RTreeAddBranch(&BranchBuf[i], q, NULL);
		else
			assert(FALSE);
	}
}

/**
 * ����һ���ڵ㣡
 * 
 * һ���ڵ��������ڵ㣡
 * 
 * �������� + ��֧ + �µĽڵ�
 */
void RTreeSplitNode(struct Node *n, struct Branch *b, struct Node **nn)
{
	register struct PartitionVars *p;
	register int level;
	RectReal area;

	assert(n);
	assert(b);

	/**
	 * ��n�����еķ�֧�ڵ���µķ�֧���ŵ�BranchBuf�У�
	 * ���ҽ�n���ã�
	 */
	level = n->level;
	RTreeGetBranches(n, b);		/* �������� + ��֧ */
	
	/* �ҵ����� */
	p = &Partitions[0];

	/**
	 * ���潫���еľ��ζ�������������
	 * 
	 * ע����������� + �ܹ�ӵ�еĽڵ������
	 */
	RTreeMethodZero(p, level>0 ? MinNodeFill : MinLeafFill);
	
	/**
	 * ����������������֮��
	 */
	area = p->area[0] + p->area[1];
	
	/* put branches from buffer in 2 nodes according to chosen partition */

	/**
	 * ���洴��һ���µĽڵ�
	 */
	*nn = RTreeNewNode();				/* �µĽڵ� */
	(*nn)->level = n->level = level;
	RTreeLoadNodes(n, *nn, p);			/* ������ԭʼ�ĸ��ڵ� + �µĽڵ�( ��������ڵ���ԭ����n���ѵõ���Ŷ ) */
										/*       p��������Ϣ */	
	assert(n->count + (*nn)->count == NODECARD+1);
}



/*-----------------------------------------------------------------------------
| Print out data for a partition from PartitionVars struct.
-----------------------------------------------------------------------------*/
static void RTreePrintPVars(struct PartitionVars *p)
{
	int i;
	assert(p);

	printf("\npartition:\n");
	for (i=0; i<NODECARD+1; i++)
	{
		printf("%3d\t", i);
	}
	printf("\n");
	for (i=0; i<NODECARD+1; i++)
	{
		if (p->taken[i])
			printf("  t\t");
		else
			printf("\t");
	}
	printf("\n");
	for (i=0; i<NODECARD+1; i++)
	{
		printf("%3d\t", p->partition[i]);
	}
	printf("\n");

	printf("count[0] = %d  area = %f\n", p->count[0], p->area[0]);
	printf("count[1] = %d  area = %f\n", p->count[1], p->area[1]);
	printf("total area = %f  effectiveness = %3.2f\n",
		p->area[0] + p->area[1],
		RTreeRectSphericalVolume(&CoverSplit)/(p->area[0]+p->area[1]));

	printf("cover[0]:\n");
	RTreePrintRect(&p->cover[0], 0);

	printf("cover[1]:\n");
	RTreePrintRect(&p->cover[1], 0);
}

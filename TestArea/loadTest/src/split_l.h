

#define METHODS 1

struct Branch BranchBuf[MAXCARD+1];		/* ��֧�Ļ����� */
int BranchCount;						/* ����BranchBuf�еķ�֧���� */
struct Rect CoverSplit;					/* �����е��Ӿ��ζ�װ��ȥ���Ǹ������� */

/**
 * Ϊ�˵�һ���ڵ���з��ѵ�ʱ����ʹ�õ�tmp
 */
struct PartitionVars
{
	int partition[MAXCARD+1];	/* ��ʾ��i���ڵ�(rect)���ڵ��Ǹ�������id */
	int total, minfill;			/* �ܵ�rect���� + ÿ����Ҷ�ڵ����ӵ�е��ӽڵ�����ٸ��� */
	int taken[MAXCARD+1];		/* ��ʾ��i���ڵ�(rect)�Ƿ��Ѿ��������� */
	int count[2];				/* ��������������ǰӵ�е�rect������ */
	struct Rect cover[2];		/* ��ǰ�Ѿ�������Ӿ����ǵĴ�İ������Σ�Ϊ�˸���İ����� */
	RectReal area[2];			/*  */
} Partitions[METHODS];


#ifndef __CARD__
#define __CARD__

/**
 * ���Ľڵ�������һ����֧���ܰ����Ľڵ�����������൱��M����������Ҫ����
 */
extern int NODECARD;
extern int LEAFCARD;

/**
 * ƽ��ڵ�ָ�ı�׼
 */
#define MinNodeFill (NODECARD / 2)	/* ���ٽ�ڵ������൱��m��������Ϊ M/2 */
#define MinLeafFill (LEAFCARD / 2)  /* ���ٽ�ڵ������൱��m��������Ϊ M/2 */

/**
 * ������Ǹ���level�ж���Ҷ�ӻ��Ƿ�Ҷ�ӽڵ㣬Ȼ�󷵻�����de���Ľڵ���
 */
#define MAXKIDS(n) ((n)->level > 0 ? NODECARD : LEAFCARD)
#define MINFILL(n) ((n)->level > 0 ? MinNodeFill : MinLeafFill)

#endif

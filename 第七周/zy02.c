#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node {
	char c;//�ַ�
	int qz;//Ȩֵ
	char bm[30];//����
	struct node *lchild, *rchild, *next, *nt;
	//�����������Һ���ָ�룬ntΪҶ��������һ�ڵ�ָ�룬next�����������������кϲ�������һ�ڵ�
} hnode;
hnode *tjzf(char *a) { //�ַ�ͳ��
	hnode *hd = (hnode *)malloc(sizeof(hnode));
	int i = 0;
	
	hd->next = NULL;
	hd->lchild = NULL;
	hd->rchild = NULL;
	hd->nt = NULL;
	
	while (a[i] != '\0') {
		hnode *p = hd->next;
		while (p != NULL) {
			if (p->c == a[i]) {//�����Ҷ���������ҵ��ַ�
				p->qz++;//Ȩֵ��
				break;
			}
			p = p->next;
		}
		if (p == NULL) { //���û���ҵ���Ҷ�������1�½ڵ�
			hnode *t = (hnode *)malloc(sizeof(hnode));
			t->c = a[i];
			t->qz = 1;
			t->lchild = NULL;
			t->rchild = NULL;
			t->bm[0] = '\0';

			t->next = hd->next;
			hd->next = t;

			t->nt = hd->nt;
			hd->nt = t;
		}
		i++;
	}
	return hd;
}
void select(hnode *hd) {//ѡ�� 
	while (hd->next->next != NULL) {
		hnode *m = hd, *p = m->next, *min1, *min2;

		while (p->next != NULL) { //p��mһֱָ��ȽϽ���ǰһ���
			if (p->next->qz < m->next->qz) {
				m = p;
			}
			p = p->next;
		}

		//ѭ��֮��mָ����С����ǰһ�ڵ�
		min1 = m->next; //minָ���һ��С���
		m->next = min1->next; //����С���ժ��

		m = hd, p = m->next;
		while (p->next != NULL) { //�ҵڶ���СȨֵ���
			if (p->next->qz < m->next->qz) {
				m = p;
			}
			p = p->next;
		}//ѭ��֮��mָ����С����ǰһ���
		min2 = m->next; //min2ָ��ڶ�С���
		m->next = min2->next; //���ڶ�С���ժ��

		m = (hnode *)malloc(sizeof(hnode));
		m->qz = min1->qz + min2->qz; //����СȨֵ�ϳ�һ���µĽ��
		m->lchild = min1;
		m->rchild = min2;
		m->next = hd->next;
		m->bm[0] = '\0';
		hd->next = m;
	}
}
void blx(hnode *hd,char cc[30],int t)//����
{
	if(hd!=NULL){
		if(t==0){
			strcat(hd->bm,cc);
			strcat(hd->bm,"0");//���������0
		}
		else if(t==1){
			strcat(hd->bm,cc);
			strcat(hd->bm,"1");//���������1
		}
		blx(hd->lchild,hd->bm,0);//�ݹ���ô���������
		blx(hd->rchild,hd->bm,1);//�ݹ鴦��������
	}
}
void freetree(hnode *t)//�ͷ�
{
	if(t!=NULL){
		freetree(t->lchild);
		freetree(t->lchild);
		free(t);
		
	}
}
void main() {
	char a[200] = "adsafeadwaasddsdfgdfsefsdafsefef";
	hnode *head, *p, *hd = (hnode*)malloc(sizeof(hnode));
	head = tjzf(a);
	hd->nt = head->nt;

	select(head);
	blx(head->next, head->bm, -1);
	p = hd->nt;
	while (p != NULL) {
		printf("%c:%d:%s\n", p->c, p->qz, p->bm); //��ʾ��Ҷ�ӽ����ַ���Ȩֵ������
		p = p->nt;
	}
	freetree(head->next);
}


#include <stdio.h>
#include <stdlib.h>


typedef struct linkedList{
    int e1,e2,wv;
    struct linkedList *next;
}linkedList;

//���� ���Ḯ��Ʈ ����ų ������
linkedList* head=NULL;


void makeLinkList(int e1,int e2,int wv){

    //���� �޸� �Ҵ�޾� ���� ����
    linkedList* p=(linkedList*)malloc(sizeof(linkedList));
    p->e1=e1;
    p->e2=e2;
    p->wv=wv;
    p->next=NULL;

    //ó�� ����Ű�� ���� ���� ��
    if(head==NULL){
        head=p;
        return;
    }

    //������ ���� ũ���� ���� ����
    linkedList* current=head;

    //current �տ� ����Ű�� ������
    linkedList* temp;

    //���� ���� head�����Ͽ� ������ �˻�
    while(current!=NULL){
        //current�� ���� ���
        if(current->wv<=p->wv){
            if(current->next==NULL){
                current->next=p;
                break;
            }
            temp=current;
            current=current->next;
        }
        //current�� Ŭ ���
        else{
            //ó���� �߰��� ��
            if(current==head){
                p->next=current;
                head=p;
                break;
            }
            temp->next=p;
            p->next=current;
            break;
        }
    }

}

void crustal_search(int edgeCount){

    FILE*fp=fopen("201879004_result.txt","w");

    linkedList *c=head;
    fprintf(fp,"\n==== ������ ���� ���� ====\n\n");
    for(c;c!=NULL;c=c->next){
        fprintf(fp,"%d %d %d\n",c->e1,c->e2,c->wv);
    }

    linkedList* p=head;
    int edgeLink[edgeCount];
    int cost=0;;
    int count=0;

    //����Ʈ�� ����Ŭ �˾Ƴ� ����
    for(int i=0;i<edgeCount;i++){
        edgeLink[i]=i;
    }

    fprintf(fp,"\n==== ���� ������ ====\n\n");
    //���� ũ���� �־��⿡ ������� �ְ� ����Ŭ�� ���ָ� ��
    for(p;p!=NULL;p=p->next){

        //����Ŭ ���� ��
        if(edgeLink[p->e1]==edgeLink[p->e2])
            continue;

        int n=edgeLink[p->e2];

        for(int i=0;i<edgeCount;i++){
            if(edgeLink[i]==n){
                edgeLink[i]=edgeLink[p->e1];
            }
        }

        cost+=p->wv;

        fprintf(fp,"(%d %d)=> cost==%d\n",p->e1,p->e2,cost);

        count++;
        if(count==(edgeCount-1)){
            break;
        }

    }

    fprintf(fp,"\n�� �ڽ�Ʈ: %d\n",cost);
    fclose(fp);
}

int main()
{
    FILE* fp=fopen("201879004_line.txt","r");

    int edgeCount;
    fscanf(fp,"%d",&edgeCount);
    int lineCount;
    fscanf(fp,"%d",&lineCount);

    for(int i=0;i<lineCount;i++){
        int edge1,edge2,weighted_Value;

        fscanf(fp,"%d %d %d",&edge1,&edge2,&weighted_Value);
        makeLinkList(edge1,edge2,weighted_Value);
        //printf("%d %d %d\n",edge1,edge2,weighted_Value);
    }

    crustal_search(edgeCount);

    fclose(fp);
    return;
}

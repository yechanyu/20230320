#include <stdio.h>
#include <stdlib.h>


typedef struct linkedList{
    int e1,e2,wv;
    struct linkedList *next;
}linkedList;

//간선 연결리스트 가르킬 포인터
linkedList* head=NULL;


void makeLinkList(int e1,int e2,int wv){

    //동적 메모리 할당받아 정보 저장
    linkedList* p=(linkedList*)malloc(sizeof(linkedList));
    p->e1=e1;
    p->e2=e2;
    p->wv=wv;
    p->next=NULL;

    //처음 가르키는 것이 없을 때
    if(head==NULL){
        head=p;
        return;
    }

    //간선값 작은 크기대로 정보 저장
    linkedList* current=head;

    //current 앞에 가르키는 포인터
    linkedList* temp;

    //들어온 값이 head부터하여 끝까지 검사
    while(current!=NULL){
        //current가 작을 경우
        if(current->wv<=p->wv){
            if(current->next==NULL){
                current->next=p;
                break;
            }
            temp=current;
            current=current->next;
        }
        //current가 클 경우
        else{
            //처음에 발견할 때
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
    fprintf(fp,"\n==== 데이터 정보 모음 ====\n\n");
    for(c;c!=NULL;c=c->next){
        fprintf(fp,"%d %d %d\n",c->e1,c->e2,c->wv);
    }

    linkedList* p=head;
    int edgeLink[edgeCount];
    int cost=0;;
    int count=0;

    //신장트리 사이클 알아낼 정보
    for(int i=0;i<edgeCount;i++){
        edgeLink[i]=i;
    }

    fprintf(fp,"\n==== 연결 순서도 ====\n\n");
    //작은 크기대로 넣었기에 순서대로 넣고 사이클만 없애면 됨
    for(p;p!=NULL;p=p->next){

        //사이클 생길 때
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

    fprintf(fp,"\n총 코스트: %d\n",cost);
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

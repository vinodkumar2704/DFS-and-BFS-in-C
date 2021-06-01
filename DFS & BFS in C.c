
#include <stdio.h> 
#include <stdlib.h> 


struct AdjListNode 
{ 
	int dest; 
	struct AdjListNode* next; 
	int c;
}; 
  

struct AdjList 
{ 
	struct AdjListNode *head;  
}; 

struct Graph 
{ 
	int n; 
	struct AdjList* array; 
}; 

struct node{
	int data;
	struct node* next;
};
struct queue{
	struct node* head;
	struct node* tail;
};


struct node* CREATE_NODE(int k){
	struct node* temp = (struct node* ) malloc(sizeof(struct node));
	temp->data=k;
	temp->next= NULL;
	return temp;
}

struct queue* ENQUEUE(struct queue* q,int k){
	struct node* temp = CREATE_NODE(k);
	if (q->head == NULL && q->tail == NULL){
		q->head = temp;
		q->tail = temp;
	}
	else{
		q->tail->next = temp;
		q->tail = temp;
	}
	return q;
}


int DEQUEUE(struct queue* q){
	
	if (q->head == NULL && q->tail == NULL){
		return -1;
	}
	else if(q->head == q->tail){
		q->head = NULL;
		int temp = q->tail->data;

		q->tail = NULL;
		return temp;
		
	}
	else{
		int temp = q->head->data;
		struct node* ptr = q->head;
		q->head = q->head->next;
		ptr->next = NULL;
		free(ptr);
		return temp;
	}
}

struct AdjListNode* newAdjListNode(int dest) 
{ 
	struct AdjListNode* newNode = 
	(struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->next = NULL; 
	newNode->c = 0;
	return newNode; 
} 
  
struct Graph* createGraph(int v) 
{ 
	struct Graph* graph =  
	(struct Graph*) malloc(sizeof(struct Graph)); 
	graph->n = v; 


	graph->array = (struct AdjList*) malloc(v * sizeof(struct AdjList)); 

	int i; 
	for (i = 0; i < v; ++i) {
	graph->array[i].head = NULL; }

	return graph; 
} 
  
struct Graph* addEdge(struct Graph* graph, int src, int dest) 
{ 
   
	struct AdjListNode* newNode = newAdjListNode(dest); 
	struct AdjListNode* temp = graph->array[src].head;
	if(temp == NULL){
	graph->array[src].head = newNode;
	return graph;
	}
	while(temp->next != NULL){temp = temp->next;}
	temp->next = newNode;
	
	return graph;
     
  
} 

void BFS(struct Graph* graph,int v){
	int n = graph->n;
	int A[n];
	for(int i= 0;i<n;i++){
		A[i] = 0;
	}
	struct queue* q = (struct queue*)malloc(sizeof(struct queue));
	q->head = NULL;
	q->tail = NULL;
	
	A[v] = 1;
	q = ENQUEUE(q,v);
	while(q->head != NULL){
		int x = DEQUEUE(q);
		printf("%d ",x);
		struct AdjListNode* temp = graph->array[x].head;
		
		while(temp != NULL){
		if(A[temp->dest] == 0){
		q = ENQUEUE(q,temp->dest);
		A[temp->dest] =1;
		}
		temp = temp->next;
		}
	}
	printf("\n");
}
void DFSVISIT(struct Graph* graph,struct AdjListNode* u){
	u->c = 'g';
	struct AdjListNode* temp = u;
	while(temp != NULL){
		if(temp->c == 'w'){
			DFSVISIT(graph,temp);
		}
		temp = temp->next;
		
	}
	u->c = 'b';
	return;
}
void DFS(struct Graph* graph,int v){

	struct AdjListNode* temp = graph->array[v].head;
	
	temp->c = 1;
	printf("%d ",v);
	while(temp != NULL){
	 int cv = temp->dest;
	 if(graph->array[cv].head->c == 0){
	 	DFS(graph,cv);
	 }
	 temp = temp->next;
	}
	

}



void main() 
{ 
	int v,n,m,i,a,b;
	scanf("%d %d",&n,&m);
	struct Graph* graph = createGraph(n); 
	for(i=0;i<m;i++){
	scanf("%d %d",&a,&b);
	graph = addEdge(graph, a, b); 
	}
	scanf("%d",&v);

    	BFS(graph,v);
    	
    	DFS(graph,v);
    	printf("\n");
} 





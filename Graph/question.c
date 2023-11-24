  GRAPH* newgraph= (GRAPH*)malloc(sizeof(GRAPH));
  newgraph->v=v;
  for(int i=0; i<v; i++)
  {
    for(int j=0;j<v;j++)
        (newgraph->arr)[i][j] = 0;
  }
  return newgraph;
}

void add_edge(GRAPH* g,int v,int w)
{
  if(w<g->v && v<g->v)
  {
    (g->arr)[v][w]=1;
    printf("Data Inserted\n");
  }
  else
    printf("Invalid input\n");
}

void destroy_graph(GRAPH* g)
{
  free(g);
}

void bfs(GRAPH* g,int s)
{
  if(s>g->v)
  {
    printf("The given source in too big\n");
    return;
  }
  int visited[MAX];
  for(int i=0;i<g->v;i++)
    visited[i]=0;
  int queue[MAX];
  int rear=0;
  int front=0;
  visited[s]=1;
  queue[rear++]=s;
  while(rear!=front)
  {
    s=queue[front++];
    printf("%d ",s);
    for(int i=0;i<g->v;i++)
    {
      if(g->arr[s][i] && !visited[i])
      {
        visited[i]=1;
        queue[rear++]=i;
      }
    }
  }
  printf("\n");
}


void delete_edge(GRAPH* g,int v,int w)
{
  if(w<g->v && v<g->v)
  {
    (g->arr)[v][w]=0;
    printf("Data Inserted\n");
  }
  else
    printf("Invalid input\n");

}


typedef struct llst{
  int data;
  struct llst* next;
}LLST;

typedef struct graph2{
  int v;
  LLST* p; 
}GRAPH2;


GRAPH2* create2(int v)
{
  GRAPH2* newgraph = (GRAPH2*)malloc(sizeof(GRAPH2));
  newgraph->v=v;
  newgraph->p = (LLST*)malloc(sizeof(LLST)*v);
  LLST* temp = newgraph->p;
  for(int i=0;i<v;i++)
  {
    temp->next=NULL;
    temp++;
  }
  temp=NULL;
  return newgraph;
}

LLST* create3(int data)
{
  LLST* newnode=(LLST*)malloc(sizeof(LLST));
  newnode->next=NULL;
  return newnode;
}


LLST* insert_sort(LLST* temp, int w)
{
  if(temp == NULL)
  {
    LLST* newnode=create3(w);
    return newnode;
  }
  else if(temp->next == NULL || w < temp->next->data)
  {
    if(temp->data > w)
    {
      LLST* newnode=create3(w);
      newnode->next=temp;
      temp=newnode;
      return temp;
    }
    else
    {
      LLST* newnode=create3(w);
      newnode->next=temp->next;
      temp->next=newnode;
      return temp;
    }
  }
  else
  {
    LLST* temp2 = temp;
    while(temp2->next!=NULL && temp2->next->data < w)
       temp2=temp2->next;
    LLST* newnode=create3(w);
    newnode->next=temp2->next;
    temp2->next=newnode;
    return temp;
  }
  return temp;
}

void add_edge_2(GRAPH2* g, int v , int w)
{
  if(v < g->v && w < g->v) 
  {
    LLST* temp = g->p +v;
    temp->data = v;
    LLST* temp2 = temp->next;
    temp->next = insert_sort(temp2,w);
  }
  else
    printf("Invalid input");
}

int search(GRAPH2* g,int v,int w)
{
  LLST* temp=g->p;
  for(int i=0;i<g->v;i++)
  {
    if(temp->data==v)
      break;
    temp++;
  }
  if(temp->data != v)
    return 0;
  else
  {
    while(temp!=NULL && temp->data!=w)
      temp=temp->next;
    if(temp->data==w)
      return 1;
    else
      return 0;
  }
  return 0;
}

LLST* delete(LLST* temp,int w)
{
  if(temp==NULL)
  {
    printf("The given graph has no edge for the given v\n");
    return NULL;
  }
  else if(temp->data == w)
  {
    LLST* temp2=temp->next;
    free(temp2);
    return temp2;
  }
  else
  {
    LLST* temp2=temp;
    LLST* temp3=temp;
    while(temp2->next->data != w && temp2!=NULL)
    {
      if(temp2!=temp)
        temp3=temp->next;
      temp2=temp2->next;
    }
    if(temp2==NULL)
    {
      printf("The given element %d is not connected to v",w);
      return temp;
    }
    else if(temp2==temp->next)
    {
      temp->next=temp2->next; 
      free(temp2);
      return temp;
    }
    else
    {
      temp3->next=temp2->next;
      free(temp2);
      return temp;
    }
  }
}

void delete_edge_2(GRAPH2* g, int v, int w)
{
  if(v > g->v || w > g->v)
    printf("Invalid input");
  else
  {
    LLST* temp=g->p +v;     
    temp->next=delete(temp->next,w);
  }
}


void bfs_2(GRAPH2* g , int s)
{
  if(!search(g,s,0))
  {
    printf("%d not found in the graph\nPls try again\n",s);
    return;
  }
  int visited[MAX];
  for(int i=0;i<g->v;i++)
    visited[i]=0;
  int queue[MAX];
  int rear=0;
  int front=0;
  visited[s]=1;
  queue[rear++]=s;
  LLST* row;
  LLST* col;
  for(int i=0;i< g->v;i++) 
  {
     s=queue[front++];
     printf("%d ",s);
     if(!visited[i] && search(g,s,i))
     {
      visited[i]=1;
      queue[rear++]=i;
    }
  }
}


int main()
{
  int v;
  printf("Enter the no.of vertices to enter:- ");
  scanf("%d",&v);
  GRAPH* g=create(v);
  printf("Note:-\n If u gave n as the no.of vertices then the range(states or vertices) is from 0....n-1\n");
  int choice;
  int w;
  while(1)
  {
    printf("1.Insert an edge from v1 to v2\n2.Delete an edge\n3.BFS\n4.Exit\nEnter your choice:- ");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1:
        printf("Enter v1:- ");
        scanf("%d",&v);
        printf("Enter v2:- ");
        scanf("%d",&w);
        add_edge(g,v,w);
        break;
      case 2:
        printf("Enter v1:- ");
        scanf("%d",&v);
        printf("Enter v2:- ");
        scanf("%d",&w);
        delete_edge(g,v,w);
        break;
      case 3: 
        printf("BFS\n");
        int s;
        printf("Enter the source from where u want to print:- \n");
        scanf("%d",&s);
        bfs(g,s);
        break;
      case 4:
        destroy_graph(g);
        printf("BYE BYE!!!");
        exit(0);
      default :
        printf("Invalid choice");
        break;
    }
  }
}









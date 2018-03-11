#include <iostream>
#include <vector>
#include <queue>
#include <vector>

using namespace std;

bool visit[100001];

struct node {
    int id;
    double weight;
    vector<node*> v;
    long double total_weight;
    long int child_count;
    bool is_child;

    node(int i, int w){
        id = i;
        weight = w;
        is_child = 0;
        child_count = 0;
        total_weight = 0;
    }
};

long double dfs(node* root){
    long double sum;
    int count = 0;
    for(int i = 0; i < root->v.size();i++){
        if (visit[root->v[i]->id] == 0){
            visit[root->v[i]->id] = 1;
            count++;
            sum = dfs(root->v[i]);
            root->total_weight +=sum;
        }
    }
    //cout << root->id << " " << root->total_weight << endl;
    if (count == 0) {
        root->total_weight += root->weight;
    }
    else{
        root->total_weight = (root->total_weight/count) + root->weight;
    }
    sum = root->total_weight;
    return sum;
}
void traverse_util(vector<node*> graph, int id, int size) {
    int n = size;
    for(int i = 1; i <= n; i++){
        visit[i] = 0;
    }
    visit[id] = 1;
    long double sum = dfs(graph[id]);
//    for (int i = 1; i <= n; i++) {
//        cout << graph[i]->id << " " << graph[i]->total_weight << endl;
//    }
    for (int i = 1; i <= n; i++){
        visit[i] = 0;
    }
    queue<node*> q;
    visit[id] = 1;
    q.push(graph[id]);
    node* root = NULL;
    node* temp = NULL;
    long double current_weight = 0;
    long double current_count = 0;
    while(q.size() != 0) {
        root = q.front();
        q.pop();
        for(int i = 0; i < root->v.size(); i++){
            if (visit[root->v[i]->id] == 0){
                temp = root->v[i];
                visit[temp->id] = 1;
                current_weight = root->total_weight - root->weight;
                current_count = (double)root->v.size();
                if (current_count > 1) {
                    current_weight = current_weight - (temp->total_weight/current_count);
                    current_weight = current_weight*(current_count/(current_count-1)) + root->weight;
                    temp->total_weight = ((temp->total_weight - temp->weight)*(temp->v.size()-1) + current_weight)/(double)temp->v.size() + temp->weight;
                }
                q.push(temp);
            }
        }
    }
//    for (int i = 1; i <= n; i++) {
//        cout << graph[i]->id << " " << graph[i]->total_weight << endl;
//    }

    double estimate = 0.0;
    double min = graph[1]->total_weight;
    int index = 1;
    for (int i = 2; i <= n; i++) {
        estimate = graph[i]->total_weight;
        if (estimate < min ){
            min = estimate;
            index = i;
        }
    }
    cout << index << endl;
    return;
}
int main(){
    int n;
    int weight;
    cin >> n;
    node *question;
    vector<node*> questions(n+1);
    for (int i = 1; i <= n; i++){
        cin >> weight;
        questions[i] = new node(i,weight);
    }
    int q1,q2;
    for(int i = 1; i < n; i++){
        cin >> q1 >> q2;
        questions[q1]->v.push_back(questions[q2]);
        questions[q2]->v.push_back(questions[q1]);
    }
    int temp_count = 0;
    int temp_id = 0;
    for(int i = 1; i <= n; i++) {
        if (questions[i]->v.size() == 1){
            questions[i]->child_count = 1;
            questions[i]->is_child = 1;
        }
        if (questions[i]->v.size() > temp_count){
            temp_count = questions[i]->v.size();
            temp_id = i;
        }
    }
//    cout << "root " << temp_id << " " << temp_count << endl;
    traverse_util(questions,temp_id,n);
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

class node
{
    public:
        bool isleaf;
    vector<int> keys;
    vector<node*> ptr;
        node();
        virtual ~node();

    protected:

    private:
};

node::node()
{

}

node::~node()
{
    //dtor
}

class bplustree
{
    node *root;
    int datasize;
    int d,t;
    int indexsize;
    int noofdatanodes;
    int noofindexnodes;
    public:
        bplustree(int,int);
        void insertinbpt(int);
        void display();
        virtual ~bplustree();

    protected:

    private:
        void insertinternalnode(int,node*,node*);
        node* findparent(node*,node*);
};

bplustree::bplustree(int d1, int t1)
{
    root = nullptr;
    this->datasize = 2*d1;
    this->indexsize = 2*t1 + 1;
    this->d = d1;
    this->t = t1;
    noofdatanodes=0;
    noofindexnodes=0;
}

void bplustree::insertinbpt(int x)
{
    //inserting for the first time
    if(root == nullptr)
    {
        root = new node;
        root->keys.push_back(x);
        root->isleaf = true;
        noofdatanodes++;
    }
    // else searching for its appropriate position
    else{
        node *curr = root; // traverse through tree from root
        node *parent ;

        //till curr reaches leaf node
        while(curr->isleaf == false)
        {
            parent = curr;

            for(int i=0; i<(int)curr->keys.size(); i++)
            {
                //
                if(x < curr->keys[i])
                {
                    curr = curr->ptr[i];
                    break;
                }

                if( i== curr->keys.size() -1)
                {
                    curr = curr->ptr[i+1];
                    break;
                }
            }
        }


    if((int)curr->keys.size() < datasize )
    {
        curr->keys.push_back(x);
        sort(curr->keys.begin(),curr->keys.end());
    }
    else
    {
        // create a new leaf node
        node* newleaf = new node;
        newleaf->isleaf = true;
        curr->keys.push_back(x);
        sort(curr->keys.begin(),curr->keys.end());
        for(auto it = curr->keys.begin()+d;it!=curr->keys.end();it++)
        {
            newleaf->keys.push_back(*it);
        }
        curr->keys.erase(curr->keys.begin()+d,curr->keys.end());
        noofdatanodes++;
        if(curr == root)
        {
            node *newroot = new node;
            newroot->isleaf = false;
            newroot->keys.push_back(newleaf->keys[0]);
            newroot->ptr.push_back(curr);
            newroot->ptr.push_back(newleaf);
            root = newroot;
            noofindexnodes++;
        }
        else
        {
            insertinternalnode(newleaf->keys[0],parent,newleaf);
        }
    }
}
}

void bplustree::insertinternalnode(int val,node* curr,node* newleaf)
{
    if((int)curr->keys.size() < indexsize)
    {
        curr->keys.push_back(val);
        sort(curr->keys.begin(),curr->keys.end());
        node *temp = new node;
        curr->ptr.push_back(temp);
        auto it = find(curr->keys.begin(),curr->keys.end(),val);
        int k=it-curr->keys.begin();
        for(int i = curr->ptr.size() -1;i>(k+1);i-- )
        {
            curr->ptr[i] = curr->ptr[i-1];
        }
        curr->ptr[k+1] = newleaf;
    }
    else
    {
        node *newindexnode = new node;
        newindexnode->isleaf=false;
        curr->keys.push_back(val);
        sort(curr->keys.begin(),curr->keys.end());
        auto it = find(curr->keys.begin(),curr->keys.end(),val);
        int k=it-curr->keys.begin();
        node *temp = new node;
        curr->ptr.push_back(temp);
        for(int i = curr->ptr.size() -1;i>(k+1);i-- )
        {
            curr->ptr[i] = curr->ptr[i-1];
        }
        curr->ptr[k+1] = newleaf;
        auto it2 = curr->keys.begin() + t;
        int sep = *it2;
        for(auto j =it2+1; j!=curr->keys.end(); j++)
        {
            newindexnode->keys.push_back(*j);
        }
        curr->keys.erase(it2,curr->keys.end());

        auto it1 = curr->ptr.begin() + t;
        for(auto j =it1+1; j!=curr->ptr.end(); j++)
        {
            newindexnode->ptr.push_back(*j);
        }
        curr->ptr.erase(it1+1,curr->ptr.end());
        noofindexnodes++;
        if(curr == root)
        {
            node* newroot = new node;
            newroot->keys.push_back(sep);
            newroot->isleaf=false;
            newroot->ptr.push_back(curr);
            newroot->ptr.push_back(newindexnode);
            root = newroot;
            noofindexnodes++;
        }
        else
        {
            insertinternalnode(sep,findparent(root,curr),newindexnode);
        }
    }
}

node* bplustree::findparent(node* curr,node *child)
{
    node* parent;
    if(curr->isleaf || curr->ptr[0]->isleaf)
    {
        return nullptr;
    }
    else
    {
        for(int i=0; i<(int)curr->ptr.size(); i++)
        {
            if(curr->ptr[i] == child)
            {
                parent = curr;
                return parent;
            }

            else
            {
                parent = findparent(curr->ptr[i],child);
                if(parent !=nullptr)
                {
                    return parent;
                }
            }
        }

    }
    return parent;
}

void bplustree::display()
{
    cout<<noofindexnodes<<" "<<noofdatanodes<<" ";

    for(auto i = root->keys.begin(); i!=root->keys.end(); i++)
    {
        cout<<*i<<" ";
    }
    cout<<"\n";
}


bplustree::~bplustree()
{
    //dtor
}






int main()
{
    int d,t;
    cin>>d>>t;
    bplustree b(d,t);
    int n=0;

    while(n!=3)
    {
        cin>>n;
        if(n==1)
        {
            int val;
            cin>>val;
            b.insertinbpt(val);
        }
        else if(n==2)
        {
            b.display();
        }

    }
    return 0;
}
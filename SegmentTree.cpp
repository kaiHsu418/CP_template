class SegTreeNode{
public:
    SegTreeNode* left = NULL;
    SegTreeNode* right = NULL;
    int start, end;
    int info; // for the node value
    int delta; // for the lazy tag added value
    bool tag; // for the lazy tag

    SegTreeNode(int a, int b, int val){
        start = a, end = b;
        delta = 0, tag = 0;
        if(a == b){
            info = val;
            return;
        }
        int mid = (a+b)/2;
        if(!left){
            left = new SegTreeNode(a, mid, val);
            right = new SegTreeNode(mid+1, b, val);
            info = left->info+right->info;
        }
    }

    SegTreeNode(int a, int b, vector<int>& v){
        start = a, end = b;
        delta = 0, tag = 0;
        if(a == b){
            info = v[a];
            return;
        }
        int mid = (a+b)/2;
        if(!left){
            left = new SegTreeNode(a, mid, v);
            right = new SegTreeNode(mid+1, b, v);
            info = left->info+right->info;
        }
    }

    void pushDown(){
        if(tag == 1 && left){
            left->info += delta*(left->end-left->start+1);
            left->delta += delta;
            left->tag = 1;
            right->info += delta*(right->end-right->start+1);
            right->delta += delta;
            right->tag = 1;
            delta = 0;
            tag = 0;
        }
    }

    void updateRangeBy(int a, int b, int val){
        if(b < start || a > end){
            return;
        }
        if(a <= start && end <= b){
            info += (end-start+1)*val;
            delta += val;
            tag = 1;
            return;
        }
        if(left){
            pushDown();
            left->updateRangeBy(a, b, val);
            right->updateRangeBy(a, b, val);
            info = left->info+right->info;
        }
    }

    int queryRange(int a, int b){
        if(b < start || a > end){
            return 0;
        }
        if(a <= start && end <= b){
            return info;
        }
        if(left){
            pushDown();
            return left->queryRange(a, b)+right->queryRange(a, b);
        }
        return -1;
    }
};
// usage: SegTreeNode* root = new SegTreeNode(0, n-1, vector or val);

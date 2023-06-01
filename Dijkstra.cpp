
//Dijkstra不能处理负权边，
//时间复杂度 ： m * insert() + n * get_min() + n * decrease_key() 
class Solution 
{
public:
    //pair的优先级队列会自动按照第一个键值进行排序
    //优先级需要自己定义，class自已写<的友元重载
    //如果是int直接使用 greater<int> 从小到大 ，less<int>从大到小
  
  
    //这里定义的输入： 
    //times
    [
      //边起点，边终点，边权值
      [2，3，1]
      [4，2，2]
      ...
      [5，3，2]
    ]
    //n是图中顶点的个数
    //k是源点
     
    int networkDelayTime(vector<vector<int>>& times, int n, int k) 
    {
        //初始化路径最大值
        const int inf = INT_MAX;

        //创建邻接表
        vector<vector<pair<int, int>>> g(n+1);
        for(auto& t: times){
            g[t[0]].emplace_back(t[1], t[2]);
        }

        //设置距离向量
        vector<int> dist(n+1, inf);

        //设置是否访问的数组
        vector<int> flag(n+1,0);

        //起点的数组距离设为0
        dist[k] = 0;
        
        //设置优先级队列
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;

        //加入初始的点
        q.emplace(0, k);

        //不断循环知道所有的点最小距离都被求出
        while(!q.empty())
        {
            //取出当前的节点
            auto p = q.top();
            q.pop();
            int dis = p.first;
            int cur_point = p.second;

            //这个节点是否已经确定了最短路径
            if(flag[cur_point]==0)
            {
                    //遍历它的所有邻居
                    for(auto& e: g[cur_point])
                    {

                        int y = e.first, d = dist[cur_point] + e.second;
                        //如果距离变小，那么加入优先级队列
                        if(d < dist[y])
                        {
                            dist[y] = d;
                            q.emplace(d, y);
                        }
                    }
                 flag[cur_point]=1;   
            }
        }

        //找出最近距离的最大值
        int ans = *max_element(dist.begin()+1, dist.end());
        return ans == inf ? -1 : ans;
    }
};

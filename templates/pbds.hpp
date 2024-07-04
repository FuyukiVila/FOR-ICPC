#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
template <typename T, class P = std::less<T>>
using ordered_set =
    tree<T, null_type, P, rb_tree_tag, tree_order_statistics_node_update>;
/*
定义一颗红黑树
int 关键字类型
null_type无映射(低版本g++为null_mapped_type)
less<int>从小到大排序
rb_tree_tag 红黑树（splay_tree_tag）
tree_order_statistics_node_update结点更新
插入t.insert();
删除t.erase();
求k在树中是第几大:t.order_of_key();
求树中的第k大:t.find_by_order();
前驱:t.lower_bound();
后继t.upper_bound();
a.join(b)b并入a 前提是两棵树的key的取值范围不相交
a.split(v,b)key小于等于v的元素属于a，其余的属于b
T.lower_bound(x)   >=x的min的迭代器
T.upper_bound((x)  >x的min的迭代器
T.find_by_order(k) 第k个数比它小的数
*/

template <typename T, class P = std::less<T>>
using heap = __gnu_pbds::priority_queue<T, P, pairing_heap_tag>;
/*
push()  //会返回一个迭代器
top()  //同 stl
size()  //同 stl
empty() //同 stl
clear()  //同 stl
pop()  //同 stl
join(priority_queue &other)  //合并两个堆,other会被清空
split(Pred prd,priority_queue &other)  //分离出两个堆
modify(point_iterator it,const key)  //修改一个节点的值
erase(point_iterator it) //删除一个节点
*/

template <typename T, typename P = std::less<T>>
using cmap = cc_hash_table<T, P>; // 拉链法(内存小)
template <typename T, typename P = std::less<T>>
using gmap = gp_hash_table<T, P>; // 查探法(速度快)

using trie =
    __gnu_pbds::trie<std::string, null_type, trie_string_access_traits<>,
                     pat_trie_tag, trie_prefix_search_node_update>;

/*
tr.insert(string s); //插入s
tr.erase(string s); //删除s
tr.join(trie b); //将b并入tr
pair//pair的使用如下：
pair<tr::iterator,tr::iterator> range=base.prefix_range(string x);
for(tr::iterator it=range.first;it!=range.second;it++)
        cout<<*it<<' '<<endl;
//pair中第一个是起始迭代器，第二个是终止迭代器，遍历过去就可以找到所有字符串了。
*/

rope<int> *r[100000];

/*
push_back(type x): 在末尾插入x
insert(int pos, type *s,int n):
将字符串s的前n位插入rope的下标pos处，如没有参数n则将字符串s的所有位都插入rope的下标pos处
append(type *s,int pos,int n):
把字符串s中从下标pos开始的n个字符连接到rope的结尾，如没有参数n则把字符串s中下标pos后的所有字符连接到rope的结尾，如没有参数pos则把整个字符串s连接到rope的结尾
erase(int pos, int x): 在pos处删除x个元素
length(): 返回数组长度
size(): 返回数组长度
replace(pos, type *s):
从rope的下标pos开始替换成字符串x，x的长度为从pos开始替换的位数，如果pos后的位数不够就补足
substr(int pos, int len): 从pos处开始提取len个元素
copy(int pos, int x, type *s):
从rope的下标pos开始的len个字符用s代替，如果pos后的位数不够就补足
at(int x):
访问第x个元素，同rp[x]
拷贝历史版本: r[i] = new rope(*r[i - 1]);
*/
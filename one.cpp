#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 2.5e5 + 100;
const int MAXNODE = 5e5 + 100;
struct samnode {
    samnode *par, *ch[26];
    int val;
    samnode() {
        par = 0; memset(ch, 0, sizeof(ch));
        val = 0;
    }
} node[MAXNODE], *root, *last;
int size = 0;
char s1[MAXN], s2[MAXN];
inline void init() {
    last = root = &node[0];
}
inline void add(int c) {
    samnode *p = last;
    samnode *np = &node[++size]; np->val = p->val + 1;
    while (p && !p->ch[c])
        p->ch[c] = np, p = p->par;
    if (!p) np->par = root;
    else {
        samnode *q = p->ch[c];
        if (q->val == p->val + 1)
            np->par = q;
        else {
            samnode *nq = &node[++size]; nq->val = p->val + 1;
            memcpy(nq->ch, q->ch, sizeof(q->ch));
            nq->par = q->par;
            q->par = np->par = nq;
            while (p && p->ch[c] == q)
                p->ch[c] = nq, p = p->par;
        }
    } last = np;
}

int main() {
    init();
    scanf("%s%s", s1, s2); int len1 = strlen(s1), len2 = strlen(s2);
    for (int i = 0; i < len1; i++)
        add(s1[i] - 'a');
    int ans = 0, curlen = 0; samnode *now = root;
    for (int i = 0; i < len2; i++) {
        int cur = s2[i] - 'a';
        if (now->ch[cur])
            now = now->ch[cur], curlen++;
        else {
            while (now && !now->ch[cur]) now = now->par;
            if (!now)
                curlen = 0, now = root;
            else
                curlen = now->val + 1, now = now->ch[cur];
        }
        ans = max(ans, curlen);
        printf("%d\n",i);
        printf("%d\n", ans);
    }
    printf("%d\n", ans);
}

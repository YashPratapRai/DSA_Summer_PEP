#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
public:
    vector <int> seg;

    SegmentTree(int n)
    {
        seg.resize(4 * n);
    }

    void build(int nodeIndex, int numsLeft, int numsRight, vector <int> &nums)
    {
        if (numsLeft == numsRight)
        {
            seg[nodeIndex] = nums[numsLeft];
            return;
        }

        int mid = ((numsLeft + numsRight) / 2);

        int leftChildIndex = ((nodeIndex * 2) + 1);
        int rightChildIndex = ((nodeIndex * 2) + 2);

        build(leftChildIndex, numsLeft, mid, nums);
        build(rightChildIndex, mid+1, numsRight, nums);

        seg[nodeIndex] = (seg[leftChildIndex] + seg[rightChildIndex]);
    }

    int query(int nodeIndex, int queryLeft, int queryRight, int numsLeft, int numsRight)
    {
        /* completely outside */
        if (numsRight < queryLeft or numsLeft > queryRight) return 0;

        /* completely inside */
        if (numsLeft >= queryLeft and numsRight <= queryRight) return seg[nodeIndex];

        int mid = ((numsLeft + numsRight) / 2);

        int leftRes = query((nodeIndex * 2) + 1, queryLeft, queryRight, numsLeft, mid);
        int rightRes = query((nodeIndex * 2) + 2, queryLeft, queryRight, mid + 1, numsRight);

        return (leftRes + rightRes);
    }

    void update(int nodeIndex, int updateIndex, int updateValue, int numsLeft, int numsRight)
    {
        if (numsLeft == numsRight)
        {
            seg[nodeIndex] = updateValue;
            return;
        }

        int mid = ((numsLeft + numsRight) / 2);

        if (updateIndex <= mid) update((nodeIndex * 2) + 1, updateIndex, updateValue, numsLeft, mid);
        else update((nodeIndex * 2) + 2, updateIndex, updateValue, mid + 1, numsRight);

        seg[nodeIndex] = (seg[(nodeIndex * 2) + 1] + seg[(nodeIndex * 2) + 2]);
    }
};

int main()
{
    vector <int> nums = {4, -3, 6, 1, 2, 5};

    int n = nums.size();

    SegmentTree *st = new SegmentTree(n);

    st->build(0, 0, n-1, nums);

    cout << "Sum of values from 2 to 4 is -: " << st->query(0, 2, 4, 0, n-1) << "\n";

    st->update(0, 2, 12, 0, 5);

    cout << "Sum of values from 2 to 4 is -: " << st->query(0, 2, 4, 0, n-1) << "\n";

    return 0;
}
class Solution {
public:
    int divide(int dividend, int divisor) {
        //对边界情况进行限制；
        //INT_MIN/-1,超过INT_MAX，需要作出限制；
        if(dividend==INT_MIN && divisor==-1) return INT_MAX;
        if(divisor==1) return dividend;

        //negative_flag标记计算结果的正负，因为为了简便计算，dividend和divisor均设置为负数；
        //用逗号作为分隔;；
        bool negative_flag = false;
        if(dividend > 0) dividend = -dividend, negative_flag ^= 1;
        if(divisor > 0) divisor = -divisor, negative_flag ^= 1;

        // div函数本质是，求有几个divisor能算出(dividend - 余数)；
        // 如果dividend > divisor商一定是0
        // 其他情况，逐个比较1,2,4,8,16,...,2n个divisor是不是超过dividend，如果超过了dividend就用剩余的重新再来。
        // 比如dividend=-45, divisor=-2，
        // 先1个，2个，4个，8个，16个，到32个会 < -45，得16
        // 再用剩余的-13计算，1个，2个，4个，到8个会 < -13，得4
        // 再用剩余的-5计算，1个，2个，到3个会 < -5，得2
        // 剩余-1 < 2，得0
        // 最后结果16+4+2+0=22
        // 1、用递归实现，复杂度是log^2(n) 递归logn层，每层需要logn来确定最高位；
        // std::function<int(int, int)> div = [&](int dividend, int divisor)->int{
        //     if(dividend > divisor) return 0;
        //     int res = 1;
        //     int step = divisor;
        //     while(dividend - step <= step){
        //         step += step;
        //         res += res;
        //     };
        //     return res + div(dividend - step, divisor);
        // };
        // 2、用移位实现,复杂度log(n);
        auto div = [](int a, int b)->int {
            if(a > b) return 0;
            int res = 0, step = b, c = 0;
            while(a - step <= step){
                step += step;
                ++c;
            }
            while(c >= 0){
                if(a <= step){
                    a -= step;                
                    res |= 1 << c;
                }
                --c;
                step >>= 1;
            }
            return res;
        };

        return negative_flag? -div(dividend, divisor):div(dividend, divisor);
    }
};
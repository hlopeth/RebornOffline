#include "Vector.h"

namespace Reborn {
    void testVector() {
#if 1
        {
            Vector2 v1(2);
            LOG_DEBUG << v1;
            Vector2 v2(1, 2);
            LOG_DEBUG << v2;
            Vector2 v3(v2);
            LOG_DEBUG << v3;
            Vector2 v4(v2.yx);
            LOG_DEBUG << v4 << "\n";
        }
        {
            Vector3 v1(2);
            LOG_DEBUG << v1;
            Vector3 v2(1, 2, 3);
            LOG_DEBUG << v2;
            Vector3 v3(v2);
            LOG_DEBUG << v3;
            Vector3 v4(v2.zyx);
            LOG_DEBUG << v4 << "\n";
        }
#endif
#if 0
        {
            Vector3 v(1, 2, 3);
            LOG_DEBUG << v;
            LOG_DEBUG << v.x;
            LOG_DEBUG << v.y;
            LOG_DEBUG << v.z;

            LOG_DEBUG << "v.xx " << v.xx;
            LOG_DEBUG << "v.xy " << v.xy;
            LOG_DEBUG << "v.xz " << v.xz;
            LOG_DEBUG << "v.yx " << v.yx;
            LOG_DEBUG << "v.yy " << v.yy;
            LOG_DEBUG << "v.yz " << v.yz;

            LOG_DEBUG << "v.xxx " << v.xxx;
            LOG_DEBUG << "v.xxy " << v.xxy;
            LOG_DEBUG << "v.xxz " << v.xxz;
            LOG_DEBUG << "v.xyx " << v.xyx;
            LOG_DEBUG << "v.xyy " << v.xyy;
            LOG_DEBUG << "v.xyz " << v.xyz;
            LOG_DEBUG << "v.xzx " << v.xzx;
            LOG_DEBUG << "v.xzy " << v.xzy;
            LOG_DEBUG << "v.xzz " << v.xzz;

            LOG_DEBUG << "v.yxx " << v.yxx;
            LOG_DEBUG << "v.yxy " << v.yxy;
            LOG_DEBUG << "v.yxz " << v.yxz;
            LOG_DEBUG << "v.yyx " << v.yyx;
            LOG_DEBUG << "v.yyy " << v.yyy;
            LOG_DEBUG << "v.yyz " << v.yyz;
            LOG_DEBUG << "v.yzx " << v.yzx;
            LOG_DEBUG << "v.yzy " << v.yzy;
            LOG_DEBUG << "v.yzz " << v.yzz;

            LOG_DEBUG << "v.zxx " << v.zxx;
            LOG_DEBUG << "v.zxy " << v.zxy;
            LOG_DEBUG << "v.zxz " << v.zxz;
            LOG_DEBUG << "v.zyx " << v.zyx;
            LOG_DEBUG << "v.zyy " << v.zyy;
            LOG_DEBUG << "v.zyz " << v.zyz;
            LOG_DEBUG << "v.zzx " << v.zzx;
            LOG_DEBUG << "v.zzy " << v.zzy;
            LOG_DEBUG << "v.zzz " << v.zzz;
        }
#endif

#if 0
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a + b;
            LOG_DEBUG << a - b;
            LOG_DEBUG << a * b << "\n";

            LOG_DEBUG << a.xy + b.xy;
            LOG_DEBUG << a.xy - b.xy;
            LOG_DEBUG << a.xy * b.xy << "\n";

            LOG_DEBUG << a + b.xy;
            LOG_DEBUG << a - b.xy;
            LOG_DEBUG << a * b.xy << "\n";

            LOG_DEBUG << a.xy + b;
            LOG_DEBUG << a.xy - b;
            LOG_DEBUG << a.xy * b << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a + b;
            LOG_DEBUG << a - b;
            LOG_DEBUG << a * b << "\n";

            LOG_DEBUG << a.xyz + b.xyz;
            LOG_DEBUG << a.xyz - b.xyz;
            LOG_DEBUG << a.xyz * b.xyz << "\n";

            LOG_DEBUG << a + b.xyz;
            LOG_DEBUG << a - b.xyz;
            LOG_DEBUG << a * b.xyz << "\n";

            LOG_DEBUG << a.xyz + b;
            LOG_DEBUG << a.xyz - b;
            LOG_DEBUG << a.xyz * b << "\n";
        }
#endif

#if 0
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " + " << b.x;
            a += b.x;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " - " << b.x;
            a -= b.x;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " * " << b.x;
            a *= b.x;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " + " << b.xx;
            a += b.xx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " - " << b.xx;
            a -= b.xx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " * " << b.xx;
            a *= b.xx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " + " << b.yy;
            a += b.yy;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " - " << b.yy;
            a -= b.yy;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " * " << b.yy;
            a *= b.yy;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " + " << b.yx;
            a += b.yx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " - " << b.yx;
            a -= b.yx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector2 a(1, 2);
            Vector2 b(1, 2);
            LOG_DEBUG << a << " * " << b.yx;
            a *= b.yx;
            LOG_DEBUG << a << "\n";
        }
#endif
#if 0
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " + " << b.z;
            a += b.z;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " - " << b.z;
            a -= b.z;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " * " << b.z;
            a *= b.z;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " + " << b.xxx;
            a += b.xxx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " - " << b.xxx;
            a -= b.xxx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " * " << b.xxx;
            a *= b.xxx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " + " << b.yyy;
            a += b.yyy;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " - " << b.yyy;
            a -= b.yyy;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " * " << b.yyy;
            a *= b.yyy;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " + " << b.zyx;
            a += b.zyx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " - " << b.zyx;
            a -= b.zyx;
            LOG_DEBUG << a << "\n";
        }
        {
            Vector3 a(1, 2, 3);
            Vector3 b(1, 2, 3);
            LOG_DEBUG << a << " * " << b.zyx;
            a *= b.zyx;
            LOG_DEBUG << a << "\n";
        }
#endif
    }
}
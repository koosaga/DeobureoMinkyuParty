
def mysqrt(x):
    lo = 1;
    hi = x;
    while lo+1!=hi:
        mi = (lo+hi)//2
        if mi*mi <= x: lo = mi
        else: hi = mi
    return lo


h = [2, 3, 6]
for i in range(30):
    h.append(4*h[-1]+17*h[-2]-12*h[-3]-16)
a = [None] * 30
for i in range(1, 30):
    a[i] = (4**i) + 3*h[i+1]*h[i]+9*h[i+1]*h[i-1] + 9*h[i]*h[i]+27*h[i]*h[i-1]-18*h[i+1]-126*h[i]-81*h[i-1]+192
    
for i in range(2, 30):
    a[i] = mysqrt(a[i])
    
    if i>=5:
        assert a[i] == 3*a[i-1]+24*a[i-2] - 16*a[i-3]
    print(i, a[i])

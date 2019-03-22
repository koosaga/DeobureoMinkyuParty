./hgen < h_perm.txt > h1.in && ./h <h1.in >h1.out && ./hnaive <h1.in >h1t.out && diff h1.out h1t.out > asd.txt

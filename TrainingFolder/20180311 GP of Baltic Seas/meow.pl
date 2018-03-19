if head == nil { } 
else {

(ps1 = nil)
s1 = head
e1 = nil
m1 = s1
t1 = s1

loop {
    if t1 == nil { break } else { t1 = t1 #next }
    m1p = m1
    m1 = m1 #next
    if t1 == nil { break } else { t1 = t1 #next }
}

if s1 #next == e1 { res1 = s1 }
else
{

    bool1 = nil
    loop {
        if bool1 == nil {
            s2 = m1
            e2 = e1
            ps2 = m1p
        }
        else
        {
            s2 = s1
            e2 = m1
            ps2 = ps1
        }
        m2 = s2
        t2 = s2 
        
        loop {
            if t2 == nil { break } else { t2 = t2 #next }
            (m2p = m2)
            m2 = m2 #next
            if t2 == nil { break } else { t2 = t2 #next }
        }
                
        <!-- Inner loop -->
        
        (if ps2 == nil { } else { ps2 #next = res2 })
        if bool1 == nil { bool1 = head } else { break }
    }
    
    <!-- s1 to tmp1, m1 to e1 -->
    
    tmp1 = m1
    if m1 #value < s1 #value {
        res1 = s1
        s1 = s1 #next
    }
    else {
        res1 = m1
        m1 = m1 #next
    }
    cur1 = res1
    loop {
        if s1 == tmp1 {
            if m1 == e1 { break } else
            {
                cur1 #next = m1
                m1 = m1 #next
            }
        }
        else
        {
            if m1 == e1
            {
                cur1 #next = s1
                s1 = s1 #next
            }
            else
            {
                if s1 #value < m1 #value
                {
                    cur1 #next = s1
                    s1 = s1 #next
                }
                else
                {
                    cur1 #next = m1
                    m1 = m1 #next
                }
            }
        }
    }
}

(head = res1)

}


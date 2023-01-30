; 假如有一个数据段
; 公司名称：DEC
; 总裁姓名：Ken Olsen
; 排   名：137
; 收   入：40
; 著名产品：PDP
; 现在我们需要更新信息
; 1. Ken Olsen在富翁榜上的排名上升至38位
; 2. DEC的收入增加了70亿美元
; 3. 该公司的著名产品变化为VAX系计算机
; 且，已知该数据段是seg，从偏移地址60H开始存放

assume cs:codesg, ds:seg

seg segment
    dw 'DEC'
    dw 'Ken Oslen'
    dw 137
    dw 40
    dw 'PDP'
seg ends

codesg segment
start:
    mov ax, seg
    mov ds, ax
    mov bx, 60h ; 因为数据是从seg:60h开始的

    mov word ptr [bx].0ch, 38 ; 排名是在ds:bx + 0ch位置，因此直接修改该字
    add work ptr [bx].0eh, 70 ; 收入是在ds:bx + 0eh位置，增加70亿

    mov si, 0
    mov byte ptr [bx].10h[si], 'V'
    inc si
    mov byte ptr [bx].10h[si], 'A'
    inc si
    mov byte ptr [bx].10h[si], 'X'

    mov ax, 4c00h
    int 21h
codesg ends

end start
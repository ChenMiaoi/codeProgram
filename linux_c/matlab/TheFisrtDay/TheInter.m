function TheInter()
    x=1:6;
    y=1:4;
    t=[12,10,11,11,13,15
       16,22,28,35,27,20
       18,21,26,32,28,25;
       20,25,30,33,32,20];
    subplot(1,2,1);
    mesh(x,y,t);
    x1=1:0.1:6;
    y1=1:0.1:4;
    [x2,y2]=meshgrid(x1,y1);
    t1=interp2(x,y,t,x2,y2,'cubic');
    subplot(1,2,2);
    mesh(x1,y1,t1);
end


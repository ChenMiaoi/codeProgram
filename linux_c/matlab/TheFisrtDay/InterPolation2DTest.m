function zi = InterPolation2DTest(x, y, z, xi, option)
% InterPolation2DTest 使用interp2(x, y, z, xi, method)来进行一维插值
    % params{
        %   x,y,z 就是二维坐标系上的点集
        %   xi 是一个位于yi的特定的标量
        %   option 是method的选择，一共四个选择，分别从0~3
        %          'nearest': 最近邻点插值，直接完成计算
        %          'spline' : 三次样条函数插值
        %          'linear' : 线性插值(缺省)，直接完成计算
        %          'cubic'  : 三次函数插值
    % }
    % return{
        %   yi 所计算得到的二元函数值
    % }
    if (option > 3) && (option < 0)
        error("option is wrong!");
    end
    method = ['nearest', 'spline', 'linear', 'cubic'];
    zi = interp1(x, y, z, xi, method = method{option});
end


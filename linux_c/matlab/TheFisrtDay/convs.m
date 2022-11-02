function output = convs(varargin)
    %convs 使用varargin计算多个多项式的和的乘积
    %conv conv()可以计算两个多项式的和的乘积
    %varargin 可变参数列表
    output = 1;
    for i = 1 : length(varargin)
        output = conv(output, varargin{i});
    end
end


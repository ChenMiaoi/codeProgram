function [minDistance, path] = FourthWork(w, start, terminal)
    % FourthWork 最短路径问题，无向图问题
    %            设P(u, v)是加权图G中从u到v的路径，则该路径的边权之和称为该路径的权，记为w(P)。
    %            从u到v的路径中权最小者P*(u, v)称为u到v的最短路径
    % Usage Dijkstra算法
    % 使用范围{
            %   1）寻求从一固定点到其余各点的最短路径
            %   2）有向图、无向图和混合图
            %   3）权非负
    % }
    % 算法思路{
            %   采用标号作业法每次迭代产生一个永久标号，从而生长一颗以v为根的最短路树
            %   在这颗树上每个顶点与根节点之间的路径皆为最短路径。
    % }
    % params{
            %   w 权值矩阵
            %   start 搜索的起点
            %   terminal 搜索的终点
    % }

    N = length(w); % 图的节点数
    D = w(start, : );

    %从起点出发，找最短距离的下一个点，每次不会重复原来的轨迹，设置queue判断节点是否访问
    queue = ones(1 : N) * inf; % 设置矩阵，并将矩阵初始化成为inf
    queue(start) = 0; % 初始化start为0
    parent = zeros(1, N); % 用于记录节点的上一个节点

    path = [];
    
    for i = 1 : N - 1
        temp = [];
        for j = 1 : N
            if queue(j)
                temp = [temp D(j)];
            else
                temp = [temp inf];
            end
        end

        [value, index] = min(temp);
        queue(index) = 0;

        for k = 1 : N
            if D(k) > D(index) + w(index, k)
                D(k) = D(index) + w(index, k);
            end
        end
    end

    minDistance = D(terminal); % 最短距离

    % 回溯法，从尾部开始寻找搜索路径
    t = terminal;
    while t ~= start && t > 0
        path = [t, path];
        p = parent(t);
        t = p;
    end

    path = [start, path];
end


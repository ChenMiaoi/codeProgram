function Print(status, move)
    % Print 输出方案
    fprintf("此岸 ----> 决策 ----> 对岸\n");
    for i = 1 : size(status, 1) - 1
        st = status(i, : );
        ed = status(i + 1, : );
        m = move(i, : );
        fprintf("(%d, %d) --> (%d, %d) --> (%d, %d)\n", ...
            st(1), st(2), m(1), m(2), ed(1), ed(2));
    end 
end


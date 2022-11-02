function [out] = decision(option)
    % decision 返回决策的第i个决策
    % D={(u,v)|u+v=1,2}
    decision_move = [
        1 0;
        0 1;
        2 0;
        1 1;
        0 2
    ];
    out = decision_move(option, : );
end


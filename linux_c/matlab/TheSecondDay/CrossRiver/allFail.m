function [new_status, new_move] = allFail(status, move)
    % allFail 五种决策都无法进行的情况，删除现有状态
    status(size(status, 1), : ) = []; % 删除现有状态
    new_status = status;
    move(size(move, 1), : ) = []; % 与现有状态同步
    new_move = move;
end


package yyx.dao;

import java.util.List;
import org.apache.ibatis.annotations.Param;
import yyx.entity.WithdrawTicket;
import yyx.entity.WithdrawTicketExample;

public interface WithdrawTicketMapper {
    long countByExample(WithdrawTicketExample example);

    int deleteByExample(WithdrawTicketExample example);

    int deleteByPrimaryKey(Integer id);

    int insert(WithdrawTicket record);

    int insertSelective(WithdrawTicket record);

    List<WithdrawTicket> selectByExample(WithdrawTicketExample example);

    WithdrawTicket selectByPrimaryKey(Integer id);

    int updateByExampleSelective(@Param("record") WithdrawTicket record, @Param("example") WithdrawTicketExample example);

    int updateByExample(@Param("record") WithdrawTicket record, @Param("example") WithdrawTicketExample example);

    int updateByPrimaryKeySelective(WithdrawTicket record);

    int updateByPrimaryKey(WithdrawTicket record);
}
package yyx.dao;

import java.util.List;
import org.apache.ibatis.annotations.Param;
import yyx.entity.AirSeat;
import yyx.entity.AirSeatExample;

public interface AirSeatMapper {
    long countByExample(AirSeatExample example);

    int deleteByExample(AirSeatExample example);

    int deleteByPrimaryKey(Integer id);

    int insert(AirSeat record);

    int insertSelective(AirSeat record);

    List<AirSeat> selectByExample(AirSeatExample example);

    AirSeat selectByPrimaryKey(Integer id);

    int updateByExampleSelective(@Param("record") AirSeat record, @Param("example") AirSeatExample example);

    int updateByExample(@Param("record") AirSeat record, @Param("example") AirSeatExample example);

    int updateByPrimaryKeySelective(AirSeat record);

    int updateByPrimaryKey(AirSeat record);
}
package yyx.dao;

import java.util.List;
import org.apache.ibatis.annotations.Param;
import yyx.entity.AirInfo;
import yyx.entity.AirInfoExample;

public interface AirInfoMapper {
    long countByExample(AirInfoExample example);

    int deleteByExample(AirInfoExample example);

    int deleteByPrimaryKey(String id);

    int insert(AirInfo record);

    int insertSelective(AirInfo record);

    List<AirInfo> selectByExample(AirInfoExample example);

    AirInfo selectByPrimaryKey(String id);

    int updateByExampleSelective(@Param("record") AirInfo record, @Param("example") AirInfoExample example);

    int updateByExample(@Param("record") AirInfo record, @Param("example") AirInfoExample example);

    int updateByPrimaryKeySelective(AirInfo record);

    int updateByPrimaryKey(AirInfo record);
}
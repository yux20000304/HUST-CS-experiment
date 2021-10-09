package yyx.entity;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class AirInfoExample {
    protected String orderByClause;

    protected boolean distinct;

    protected List<Criteria> oredCriteria;

    public AirInfoExample() {
        oredCriteria = new ArrayList<>();
    }

    public void setOrderByClause(String orderByClause) {
        this.orderByClause = orderByClause;
    }

    public String getOrderByClause() {
        return orderByClause;
    }

    public void setDistinct(boolean distinct) {
        this.distinct = distinct;
    }

    public boolean isDistinct() {
        return distinct;
    }

    public List<Criteria> getOredCriteria() {
        return oredCriteria;
    }

    public void or(Criteria criteria) {
        oredCriteria.add(criteria);
    }

    public Criteria or() {
        Criteria criteria = createCriteriaInternal();
        oredCriteria.add(criteria);
        return criteria;
    }

    public Criteria createCriteria() {
        Criteria criteria = createCriteriaInternal();
        if (oredCriteria.size() == 0) {
            oredCriteria.add(criteria);
        }
        return criteria;
    }

    protected Criteria createCriteriaInternal() {
        Criteria criteria = new Criteria();
        return criteria;
    }

    public void clear() {
        oredCriteria.clear();
        orderByClause = null;
        distinct = false;
    }

    protected abstract static class GeneratedCriteria {
        protected List<Criterion> criteria;

        protected GeneratedCriteria() {
            super();
            criteria = new ArrayList<>();
        }

        public boolean isValid() {
            return criteria.size() > 0;
        }

        public List<Criterion> getAllCriteria() {
            return criteria;
        }

        public List<Criterion> getCriteria() {
            return criteria;
        }

        protected void addCriterion(String condition) {
            if (condition == null) {
                throw new RuntimeException("Value for condition cannot be null");
            }
            criteria.add(new Criterion(condition));
        }

        protected void addCriterion(String condition, Object value, String property) {
            if (value == null) {
                throw new RuntimeException("Value for " + property + " cannot be null");
            }
            criteria.add(new Criterion(condition, value));
        }

        protected void addCriterion(String condition, Object value1, Object value2, String property) {
            if (value1 == null || value2 == null) {
                throw new RuntimeException("Between values for " + property + " cannot be null");
            }
            criteria.add(new Criterion(condition, value1, value2));
        }

        public Criteria andIdIsNull() {
            addCriterion("id is null");
            return (Criteria) this;
        }

        public Criteria andIdIsNotNull() {
            addCriterion("id is not null");
            return (Criteria) this;
        }

        public Criteria andIdEqualTo(String value) {
            addCriterion("id =", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdNotEqualTo(String value) {
            addCriterion("id <>", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdGreaterThan(String value) {
            addCriterion("id >", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdGreaterThanOrEqualTo(String value) {
            addCriterion("id >=", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdLessThan(String value) {
            addCriterion("id <", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdLessThanOrEqualTo(String value) {
            addCriterion("id <=", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdLike(String value) {
            addCriterion("id like", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdNotLike(String value) {
            addCriterion("id not like", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdIn(List<String> values) {
            addCriterion("id in", values, "id");
            return (Criteria) this;
        }

        public Criteria andIdNotIn(List<String> values) {
            addCriterion("id not in", values, "id");
            return (Criteria) this;
        }

        public Criteria andIdBetween(String value1, String value2) {
            addCriterion("id between", value1, value2, "id");
            return (Criteria) this;
        }

        public Criteria andIdNotBetween(String value1, String value2) {
            addCriterion("id not between", value1, value2, "id");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeIsNull() {
            addCriterion("Takeoff_time is null");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeIsNotNull() {
            addCriterion("Takeoff_time is not null");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeEqualTo(Date value) {
            addCriterion("Takeoff_time =", value, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeNotEqualTo(Date value) {
            addCriterion("Takeoff_time <>", value, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeGreaterThan(Date value) {
            addCriterion("Takeoff_time >", value, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeGreaterThanOrEqualTo(Date value) {
            addCriterion("Takeoff_time >=", value, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeLessThan(Date value) {
            addCriterion("Takeoff_time <", value, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeLessThanOrEqualTo(Date value) {
            addCriterion("Takeoff_time <=", value, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeIn(List<Date> values) {
            addCriterion("Takeoff_time in", values, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeNotIn(List<Date> values) {
            addCriterion("Takeoff_time not in", values, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeBetween(Date value1, Date value2) {
            addCriterion("Takeoff_time between", value1, value2, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andTakeoffTimeNotBetween(Date value1, Date value2) {
            addCriterion("Takeoff_time not between", value1, value2, "takeoffTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeIsNull() {
            addCriterion("Arrive_time is null");
            return (Criteria) this;
        }

        public Criteria andArriveTimeIsNotNull() {
            addCriterion("Arrive_time is not null");
            return (Criteria) this;
        }

        public Criteria andArriveTimeEqualTo(Date value) {
            addCriterion("Arrive_time =", value, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeNotEqualTo(Date value) {
            addCriterion("Arrive_time <>", value, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeGreaterThan(Date value) {
            addCriterion("Arrive_time >", value, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeGreaterThanOrEqualTo(Date value) {
            addCriterion("Arrive_time >=", value, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeLessThan(Date value) {
            addCriterion("Arrive_time <", value, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeLessThanOrEqualTo(Date value) {
            addCriterion("Arrive_time <=", value, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeIn(List<Date> values) {
            addCriterion("Arrive_time in", values, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeNotIn(List<Date> values) {
            addCriterion("Arrive_time not in", values, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeBetween(Date value1, Date value2) {
            addCriterion("Arrive_time between", value1, value2, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andArriveTimeNotBetween(Date value1, Date value2) {
            addCriterion("Arrive_time not between", value1, value2, "arriveTime");
            return (Criteria) this;
        }

        public Criteria andOriginStatIsNull() {
            addCriterion("origin_stat is null");
            return (Criteria) this;
        }

        public Criteria andOriginStatIsNotNull() {
            addCriterion("origin_stat is not null");
            return (Criteria) this;
        }

        public Criteria andOriginStatEqualTo(String value) {
            addCriterion("origin_stat =", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatNotEqualTo(String value) {
            addCriterion("origin_stat <>", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatGreaterThan(String value) {
            addCriterion("origin_stat >", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatGreaterThanOrEqualTo(String value) {
            addCriterion("origin_stat >=", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatLessThan(String value) {
            addCriterion("origin_stat <", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatLessThanOrEqualTo(String value) {
            addCriterion("origin_stat <=", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatLike(String value) {
            addCriterion("origin_stat like", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatNotLike(String value) {
            addCriterion("origin_stat not like", value, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatIn(List<String> values) {
            addCriterion("origin_stat in", values, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatNotIn(List<String> values) {
            addCriterion("origin_stat not in", values, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatBetween(String value1, String value2) {
            addCriterion("origin_stat between", value1, value2, "originStat");
            return (Criteria) this;
        }

        public Criteria andOriginStatNotBetween(String value1, String value2) {
            addCriterion("origin_stat not between", value1, value2, "originStat");
            return (Criteria) this;
        }

        public Criteria andTermStatIsNull() {
            addCriterion("Term_stat is null");
            return (Criteria) this;
        }

        public Criteria andTermStatIsNotNull() {
            addCriterion("Term_stat is not null");
            return (Criteria) this;
        }

        public Criteria andTermStatEqualTo(String value) {
            addCriterion("Term_stat =", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatNotEqualTo(String value) {
            addCriterion("Term_stat <>", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatGreaterThan(String value) {
            addCriterion("Term_stat >", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatGreaterThanOrEqualTo(String value) {
            addCriterion("Term_stat >=", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatLessThan(String value) {
            addCriterion("Term_stat <", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatLessThanOrEqualTo(String value) {
            addCriterion("Term_stat <=", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatLike(String value) {
            addCriterion("Term_stat like", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatNotLike(String value) {
            addCriterion("Term_stat not like", value, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatIn(List<String> values) {
            addCriterion("Term_stat in", values, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatNotIn(List<String> values) {
            addCriterion("Term_stat not in", values, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatBetween(String value1, String value2) {
            addCriterion("Term_stat between", value1, value2, "termStat");
            return (Criteria) this;
        }

        public Criteria andTermStatNotBetween(String value1, String value2) {
            addCriterion("Term_stat not between", value1, value2, "termStat");
            return (Criteria) this;
        }

        public Criteria andPriceIsNull() {
            addCriterion("price is null");
            return (Criteria) this;
        }

        public Criteria andPriceIsNotNull() {
            addCriterion("price is not null");
            return (Criteria) this;
        }

        public Criteria andPriceEqualTo(Integer value) {
            addCriterion("price =", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceNotEqualTo(Integer value) {
            addCriterion("price <>", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceGreaterThan(Integer value) {
            addCriterion("price >", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceGreaterThanOrEqualTo(Integer value) {
            addCriterion("price >=", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceLessThan(Integer value) {
            addCriterion("price <", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceLessThanOrEqualTo(Integer value) {
            addCriterion("price <=", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceIn(List<Integer> values) {
            addCriterion("price in", values, "price");
            return (Criteria) this;
        }

        public Criteria andPriceNotIn(List<Integer> values) {
            addCriterion("price not in", values, "price");
            return (Criteria) this;
        }

        public Criteria andPriceBetween(Integer value1, Integer value2) {
            addCriterion("price between", value1, value2, "price");
            return (Criteria) this;
        }

        public Criteria andPriceNotBetween(Integer value1, Integer value2) {
            addCriterion("price not between", value1, value2, "price");
            return (Criteria) this;
        }

        public Criteria andBookedseatsIsNull() {
            addCriterion("bookedseats is null");
            return (Criteria) this;
        }

        public Criteria andBookedseatsIsNotNull() {
            addCriterion("bookedseats is not null");
            return (Criteria) this;
        }

        public Criteria andBookedseatsEqualTo(Integer value) {
            addCriterion("bookedseats =", value, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsNotEqualTo(Integer value) {
            addCriterion("bookedseats <>", value, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsGreaterThan(Integer value) {
            addCriterion("bookedseats >", value, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsGreaterThanOrEqualTo(Integer value) {
            addCriterion("bookedseats >=", value, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsLessThan(Integer value) {
            addCriterion("bookedseats <", value, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsLessThanOrEqualTo(Integer value) {
            addCriterion("bookedseats <=", value, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsIn(List<Integer> values) {
            addCriterion("bookedseats in", values, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsNotIn(List<Integer> values) {
            addCriterion("bookedseats not in", values, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsBetween(Integer value1, Integer value2) {
            addCriterion("bookedseats between", value1, value2, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andBookedseatsNotBetween(Integer value1, Integer value2) {
            addCriterion("bookedseats not between", value1, value2, "bookedseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsIsNull() {
            addCriterion("totalseats is null");
            return (Criteria) this;
        }

        public Criteria andTotalseatsIsNotNull() {
            addCriterion("totalseats is not null");
            return (Criteria) this;
        }

        public Criteria andTotalseatsEqualTo(Integer value) {
            addCriterion("totalseats =", value, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsNotEqualTo(Integer value) {
            addCriterion("totalseats <>", value, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsGreaterThan(Integer value) {
            addCriterion("totalseats >", value, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsGreaterThanOrEqualTo(Integer value) {
            addCriterion("totalseats >=", value, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsLessThan(Integer value) {
            addCriterion("totalseats <", value, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsLessThanOrEqualTo(Integer value) {
            addCriterion("totalseats <=", value, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsIn(List<Integer> values) {
            addCriterion("totalseats in", values, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsNotIn(List<Integer> values) {
            addCriterion("totalseats not in", values, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsBetween(Integer value1, Integer value2) {
            addCriterion("totalseats between", value1, value2, "totalseats");
            return (Criteria) this;
        }

        public Criteria andTotalseatsNotBetween(Integer value1, Integer value2) {
            addCriterion("totalseats not between", value1, value2, "totalseats");
            return (Criteria) this;
        }
    }

    public static class Criteria extends GeneratedCriteria {
        protected Criteria() {
            super();
        }
    }

    public static class Criterion {
        private String condition;

        private Object value;

        private Object secondValue;

        private boolean noValue;

        private boolean singleValue;

        private boolean betweenValue;

        private boolean listValue;

        private String typeHandler;

        public String getCondition() {
            return condition;
        }

        public Object getValue() {
            return value;
        }

        public Object getSecondValue() {
            return secondValue;
        }

        public boolean isNoValue() {
            return noValue;
        }

        public boolean isSingleValue() {
            return singleValue;
        }

        public boolean isBetweenValue() {
            return betweenValue;
        }

        public boolean isListValue() {
            return listValue;
        }

        public String getTypeHandler() {
            return typeHandler;
        }

        protected Criterion(String condition) {
            super();
            this.condition = condition;
            this.typeHandler = null;
            this.noValue = true;
        }

        protected Criterion(String condition, Object value, String typeHandler) {
            super();
            this.condition = condition;
            this.value = value;
            this.typeHandler = typeHandler;
            if (value instanceof List<?>) {
                this.listValue = true;
            } else {
                this.singleValue = true;
            }
        }

        protected Criterion(String condition, Object value) {
            this(condition, value, null);
        }

        protected Criterion(String condition, Object value, Object secondValue, String typeHandler) {
            super();
            this.condition = condition;
            this.value = value;
            this.secondValue = secondValue;
            this.typeHandler = typeHandler;
            this.betweenValue = true;
        }

        protected Criterion(String condition, Object value, Object secondValue) {
            this(condition, value, secondValue, null);
        }
    }
}
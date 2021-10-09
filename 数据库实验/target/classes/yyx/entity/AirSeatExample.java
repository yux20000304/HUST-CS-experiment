package yyx.entity;

import java.util.ArrayList;
import java.util.List;

public class AirSeatExample {
    protected String orderByClause;

    protected boolean distinct;

    protected List<Criteria> oredCriteria;

    public AirSeatExample() {
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

        public Criteria andIdEqualTo(Integer value) {
            addCriterion("id =", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdNotEqualTo(Integer value) {
            addCriterion("id <>", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdGreaterThan(Integer value) {
            addCriterion("id >", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdGreaterThanOrEqualTo(Integer value) {
            addCriterion("id >=", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdLessThan(Integer value) {
            addCriterion("id <", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdLessThanOrEqualTo(Integer value) {
            addCriterion("id <=", value, "id");
            return (Criteria) this;
        }

        public Criteria andIdIn(List<Integer> values) {
            addCriterion("id in", values, "id");
            return (Criteria) this;
        }

        public Criteria andIdNotIn(List<Integer> values) {
            addCriterion("id not in", values, "id");
            return (Criteria) this;
        }

        public Criteria andIdBetween(Integer value1, Integer value2) {
            addCriterion("id between", value1, value2, "id");
            return (Criteria) this;
        }

        public Criteria andIdNotBetween(Integer value1, Integer value2) {
            addCriterion("id not between", value1, value2, "id");
            return (Criteria) this;
        }

        public Criteria andFlightIdIsNull() {
            addCriterion("Flight_id is null");
            return (Criteria) this;
        }

        public Criteria andFlightIdIsNotNull() {
            addCriterion("Flight_id is not null");
            return (Criteria) this;
        }

        public Criteria andFlightIdEqualTo(String value) {
            addCriterion("Flight_id =", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdNotEqualTo(String value) {
            addCriterion("Flight_id <>", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdGreaterThan(String value) {
            addCriterion("Flight_id >", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdGreaterThanOrEqualTo(String value) {
            addCriterion("Flight_id >=", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdLessThan(String value) {
            addCriterion("Flight_id <", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdLessThanOrEqualTo(String value) {
            addCriterion("Flight_id <=", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdLike(String value) {
            addCriterion("Flight_id like", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdNotLike(String value) {
            addCriterion("Flight_id not like", value, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdIn(List<String> values) {
            addCriterion("Flight_id in", values, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdNotIn(List<String> values) {
            addCriterion("Flight_id not in", values, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdBetween(String value1, String value2) {
            addCriterion("Flight_id between", value1, value2, "flightId");
            return (Criteria) this;
        }

        public Criteria andFlightIdNotBetween(String value1, String value2) {
            addCriterion("Flight_id not between", value1, value2, "flightId");
            return (Criteria) this;
        }

        public Criteria andSeatnumIsNull() {
            addCriterion("Seatnum is null");
            return (Criteria) this;
        }

        public Criteria andSeatnumIsNotNull() {
            addCriterion("Seatnum is not null");
            return (Criteria) this;
        }

        public Criteria andSeatnumEqualTo(Integer value) {
            addCriterion("Seatnum =", value, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumNotEqualTo(Integer value) {
            addCriterion("Seatnum <>", value, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumGreaterThan(Integer value) {
            addCriterion("Seatnum >", value, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumGreaterThanOrEqualTo(Integer value) {
            addCriterion("Seatnum >=", value, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumLessThan(Integer value) {
            addCriterion("Seatnum <", value, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumLessThanOrEqualTo(Integer value) {
            addCriterion("Seatnum <=", value, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumIn(List<Integer> values) {
            addCriterion("Seatnum in", values, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumNotIn(List<Integer> values) {
            addCriterion("Seatnum not in", values, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumBetween(Integer value1, Integer value2) {
            addCriterion("Seatnum between", value1, value2, "seatnum");
            return (Criteria) this;
        }

        public Criteria andSeatnumNotBetween(Integer value1, Integer value2) {
            addCriterion("Seatnum not between", value1, value2, "seatnum");
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
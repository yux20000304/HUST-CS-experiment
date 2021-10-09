package yyx.entity;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class BookExample {
    protected String orderByClause;

    protected boolean distinct;

    protected List<Criteria> oredCriteria;

    public BookExample() {
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

        public Criteria andPIdIsNull() {
            addCriterion("P_id is null");
            return (Criteria) this;
        }

        public Criteria andPIdIsNotNull() {
            addCriterion("P_id is not null");
            return (Criteria) this;
        }

        public Criteria andPIdEqualTo(Integer value) {
            addCriterion("P_id =", value, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdNotEqualTo(Integer value) {
            addCriterion("P_id <>", value, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdGreaterThan(Integer value) {
            addCriterion("P_id >", value, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdGreaterThanOrEqualTo(Integer value) {
            addCriterion("P_id >=", value, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdLessThan(Integer value) {
            addCriterion("P_id <", value, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdLessThanOrEqualTo(Integer value) {
            addCriterion("P_id <=", value, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdIn(List<Integer> values) {
            addCriterion("P_id in", values, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdNotIn(List<Integer> values) {
            addCriterion("P_id not in", values, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdBetween(Integer value1, Integer value2) {
            addCriterion("P_id between", value1, value2, "pId");
            return (Criteria) this;
        }

        public Criteria andPIdNotBetween(Integer value1, Integer value2) {
            addCriterion("P_id not between", value1, value2, "pId");
            return (Criteria) this;
        }

        public Criteria andAirInfoIsNull() {
            addCriterion("Air_info is null");
            return (Criteria) this;
        }

        public Criteria andAirInfoIsNotNull() {
            addCriterion("Air_info is not null");
            return (Criteria) this;
        }

        public Criteria andAirInfoEqualTo(String value) {
            addCriterion("Air_info =", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoNotEqualTo(String value) {
            addCriterion("Air_info <>", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoGreaterThan(String value) {
            addCriterion("Air_info >", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoGreaterThanOrEqualTo(String value) {
            addCriterion("Air_info >=", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoLessThan(String value) {
            addCriterion("Air_info <", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoLessThanOrEqualTo(String value) {
            addCriterion("Air_info <=", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoLike(String value) {
            addCriterion("Air_info like", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoNotLike(String value) {
            addCriterion("Air_info not like", value, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoIn(List<String> values) {
            addCriterion("Air_info in", values, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoNotIn(List<String> values) {
            addCriterion("Air_info not in", values, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoBetween(String value1, String value2) {
            addCriterion("Air_info between", value1, value2, "airInfo");
            return (Criteria) this;
        }

        public Criteria andAirInfoNotBetween(String value1, String value2) {
            addCriterion("Air_info not between", value1, value2, "airInfo");
            return (Criteria) this;
        }

        public Criteria andBooktimeIsNull() {
            addCriterion("Booktime is null");
            return (Criteria) this;
        }

        public Criteria andBooktimeIsNotNull() {
            addCriterion("Booktime is not null");
            return (Criteria) this;
        }

        public Criteria andBooktimeEqualTo(Date value) {
            addCriterion("Booktime =", value, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeNotEqualTo(Date value) {
            addCriterion("Booktime <>", value, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeGreaterThan(Date value) {
            addCriterion("Booktime >", value, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeGreaterThanOrEqualTo(Date value) {
            addCriterion("Booktime >=", value, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeLessThan(Date value) {
            addCriterion("Booktime <", value, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeLessThanOrEqualTo(Date value) {
            addCriterion("Booktime <=", value, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeIn(List<Date> values) {
            addCriterion("Booktime in", values, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeNotIn(List<Date> values) {
            addCriterion("Booktime not in", values, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeBetween(Date value1, Date value2) {
            addCriterion("Booktime between", value1, value2, "booktime");
            return (Criteria) this;
        }

        public Criteria andBooktimeNotBetween(Date value1, Date value2) {
            addCriterion("Booktime not between", value1, value2, "booktime");
            return (Criteria) this;
        }

        public Criteria andPriceIsNull() {
            addCriterion("Price is null");
            return (Criteria) this;
        }

        public Criteria andPriceIsNotNull() {
            addCriterion("Price is not null");
            return (Criteria) this;
        }

        public Criteria andPriceEqualTo(Integer value) {
            addCriterion("Price =", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceNotEqualTo(Integer value) {
            addCriterion("Price <>", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceGreaterThan(Integer value) {
            addCriterion("Price >", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceGreaterThanOrEqualTo(Integer value) {
            addCriterion("Price >=", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceLessThan(Integer value) {
            addCriterion("Price <", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceLessThanOrEqualTo(Integer value) {
            addCriterion("Price <=", value, "price");
            return (Criteria) this;
        }

        public Criteria andPriceIn(List<Integer> values) {
            addCriterion("Price in", values, "price");
            return (Criteria) this;
        }

        public Criteria andPriceNotIn(List<Integer> values) {
            addCriterion("Price not in", values, "price");
            return (Criteria) this;
        }

        public Criteria andPriceBetween(Integer value1, Integer value2) {
            addCriterion("Price between", value1, value2, "price");
            return (Criteria) this;
        }

        public Criteria andPriceNotBetween(Integer value1, Integer value2) {
            addCriterion("Price not between", value1, value2, "price");
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
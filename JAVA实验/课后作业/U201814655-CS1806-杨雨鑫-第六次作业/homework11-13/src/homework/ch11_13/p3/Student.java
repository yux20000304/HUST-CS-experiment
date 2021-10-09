package homework.ch11_13.p3;

import java.util.Objects;

public class Student extends Person implements Cloneable{
    private int studentId;
    private String department;
    private String classNo;

    public Student(){

    }

    public Student(String name,int age,int studentId,String department,String classNo){
        super(name, age);
        this.studentId=studentId;
        this.department=department;
        this.classNo=classNo;
    }

    public int getStudentId() {
        return studentId;
    }

    public void setStudentId(int studentId) {
        this.studentId = studentId;
    }

    public String getDepartment() {
        return department;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public String getClassNo() {
        return classNo;
    }

    public void setClassNo(String classNo) {
        this.classNo = classNo;
    }

    @Override
    public String toString(){
        return super.toString()+"classNo: "+classNo+"department: "+department+"studentId: "+studentId;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Student student = (Student) o;
        return this.getAge() == student.getAge() && Objects.equals(this.getName(), student.getName()) && studentId == student.studentId && Objects.equals(department, student.department) && Objects.equals(classNo, student.classNo);
    }

    @Override
    public Object clone() throws CloneNotSupportedException{
        Student new_student=(Student)super.clone();
        new_student.studentId=this.studentId;
        new_student.department=new String(this.department);
        new_student.classNo=new String(this.classNo);
        return new_student;
    }
}

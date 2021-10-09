package homework.ch11_13.p3;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Course implements Cloneable{
    private String courseName;
    private List<Person> students;
    private Person teacher;

    public Course(String courseName,Person teacher){
        this.courseName=courseName;
        this.teacher=teacher;
        this.students=new ArrayList<>();
    }

    public void register(Person s){

        if(!students.contains(s)&& s instanceof Student ){
            int i;
            for(i=0;i<students.size();i++) {
                if(((Student)(students.get(i))).getStudentId()>((Student)s).getStudentId()){
                    break;
                }
            }
            students.add(i,s);
        }
    }

    public String getCourseName() {
        return courseName;
    }

    public void setCourseName(String courseName) {
        this.courseName = courseName;
    }

    public List<Person> getStudents() {
        return students;
    }

    public Person getTeacher() {
        return teacher;
    }

    public void unregister(Person a){
        if(students.contains(a))
            students.remove(a);
    }

    public int getNumberOfStudent(){
        return students.size();
    }

    @Override
    public Object clone() throws CloneNotSupportedException{
        Course new_course=(Course)super.clone();
        new_course.courseName=new String(this.courseName);
        new_course.students=new ArrayList<Person>();
        for(int i=0;i<this.students.size();i++){
            new_course.students.add((Person) (this.students.get(i).clone()));
        }
        new_course.teacher=(Person) this.teacher.clone();
        return new_course;
    }
    @Override
    public String toString(){
        String info;
        info="coursename: "+courseName+"teacher: "+teacher.toString()+"student: ";
        for(int i=0;i<students.size();i++){
            info+=students.get(i);
        }
        return info;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Course course = (Course) o;
        if(students.size() != course.students.size()){
            return  false;
        }
        for(int i=0;i<students.size();i++){
            if(!students.get(i).equals(course.students.get(i)))
                return false;
        }
        return Objects.equals(courseName, course.courseName) && Objects.equals(teacher, course.teacher);
    }


    public static void main(String [] args) throws CloneNotSupportedException {
        Person teacher = new Faculty("James Gosling", 65, 0, "Professor", "http://nighthacks.com/jag/bio/index.html");

        String courseName = "Java Language Programming";
        Course c = new Course(courseName, teacher);

        Person student1 = new Student("aaa", 20, 20170101, "CS", "CS1704");
        Person student2 = new Student("bbb", 20, 20170102, "CS", "CS1705");
        Person student3 = new Student("ccc", 20, 20170103, "CS", "CS1706");
        c.register(student1);
        c.register(student2);
        c.register(student3);
        Course cloned=(Course)c.clone();
        boolean isDeepClone = true;

        for(int i = 0; i < c.getStudents().size(); ++i) {
            Person s1 = (Person)c.getStudents().get(i);
            Person s2 = (Person)cloned.getStudents().get(i);
            if (!s1.equals(s2) || s1 == s2) {
                isDeepClone = false;
                break;
            }
        }

//        Assert.assertTrue(c.equals(cloned) && c.getCourseName() != cloned.getCourseName() && c.getTeacher() != cloned.getTeacher() && c.getStudents() != cloned.getStudents() && isDeepClone);
        System.out.println(c.equals(cloned) +" " +(c.getCourseName() != cloned.getCourseName()) + " "+ (c.getTeacher() != cloned.getTeacher()) + " " + (c.getStudents() != cloned.getStudents()) + " " + isDeepClone);

    }
}

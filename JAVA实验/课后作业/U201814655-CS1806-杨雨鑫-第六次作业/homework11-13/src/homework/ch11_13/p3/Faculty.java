package homework.ch11_13.p3;

import java.util.Objects;

public class Faculty extends Person{
    private int facultyId;
    private String title;
    private String email;

    public Faculty(){

    }

    public Faculty(String name,int age,int facultyId,String title,String email){
        super(name,age);
        this.facultyId=facultyId;
        this.email=email;
        this.title=title;
    }

    public int getFacultyId() {
        return facultyId;
    }

    public void setFacultyId(int facultyId) {
        this.facultyId = facultyId;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }
    @Override
    public String toString(){
        return super.toString()+"facultyId: "+facultyId+"title: "+title+"email: "+email;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        Faculty faculty = (Faculty) o;
        return facultyId == faculty.facultyId && Objects.equals(title, faculty.title) && Objects.equals(email, faculty.email);
    }

    @Override
    public Object clone() throws CloneNotSupportedException{
        Faculty new_faculty=(Faculty) super.clone();
        new_faculty.facultyId=this.facultyId;
        new_faculty.email=new String(this.email);
        new_faculty.title=new String(this.title);
        return new_faculty;
    }
}

package yyx.entity;

public class UserInfo {
    private String username;

    private Integer id;

    private String password;

    public UserInfo(String username, Integer id, String password) {
        this.username = username;
        this.id = id;
        this.password = password;
    }

    public UserInfo() {
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username == null ? null : username.trim();
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password == null ? null : password.trim();
    }
}
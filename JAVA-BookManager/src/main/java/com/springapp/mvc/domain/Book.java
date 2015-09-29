package com.springapp.mvc.domain;

import javax.persistence.*;

@Entity
@Table (name = "books")
public class Book {

    @Id
    @Column(name = "id")
    @GeneratedValue()
    private int iD;

    @Column(name = "name")
    private String name;

    @Column(name = "genre")
    private String genre;

    /**
     *
     * @return ���������� �������������
     */
    public int getiD() {
        return iD;
    }

    /**
     *
     * @param iD ��������� �������������
     */
    public void setiD(int iD) {
        this.iD = iD;
    }

    /**
     *
     * @return ���������� ���
     */
    public String getName() {
        return name;
    }

    /**
     *
     * @param name ��������� ���
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     *
     * @return ���������� ����
     */
    public String getGenre() {
        return genre;
    }

    /**
     *
     * @param genre ��������� ����
     */
    public void setGenre(String genre) {
        this.genre = genre;
    }
}

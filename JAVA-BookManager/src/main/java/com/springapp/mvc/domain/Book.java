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
     * @return возвращает идентификатор
     */
    public int getiD() {
        return iD;
    }

    /**
     *
     * @param iD добавляет идентификатор
     */
    public void setiD(int iD) {
        this.iD = iD;
    }

    /**
     *
     * @return возвращает имя
     */
    public String getName() {
        return name;
    }

    /**
     *
     * @param name добавляет имя
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     *
     * @return возвращает жанр
     */
    public String getGenre() {
        return genre;
    }

    /**
     *
     * @param genre добавляет жанр
     */
    public void setGenre(String genre) {
        this.genre = genre;
    }
}

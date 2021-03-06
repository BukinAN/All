package com.springapp.mvc.repository;

import com.springapp.mvc.domain.Book;
import org.hibernate.SessionFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;
import org.springframework.transaction.annotation.Transactional;


import java.util.List;


@Repository
@Transactional
public class BookRepository {

    @Autowired
    private SessionFactory sessionFactory;

    /**
     *
     * @param book ��������� �����
     */
    public void addBook(Book book){
        this.sessionFactory.getCurrentSession().save(book);
    }

    /**
     *
     * @return ��������� ������ ���� ����
     */
    public List<Book> listAll(){
        return this.sessionFactory.getCurrentSession().createQuery("from Book").list();
    }

    /**
     *
     * @param iD ������� ����� �� ��������������
     */
    public void removeBook(Integer iD){
        Book contact = (Book)this.sessionFactory.getCurrentSession().load(Book.class, iD);
        if (null!=contact){
            this.sessionFactory.getCurrentSession().delete(contact);
        }
    }
}


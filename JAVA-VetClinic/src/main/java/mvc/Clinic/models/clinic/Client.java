package mvc.Clinic.models.clinic;

import mvc.Clinic.models.clinic.animals.Pet;


public class Client {
    private int id;
    private String name;
    private final Pet pet;

    /**
     *
     * @param id идентификатор клиента
     * @param name имя клиента
     * @param pet питомец
     */
    public Client(int id,String name, Pet pet) {
        this.id = id;
        this.name = name;
        this.pet = pet;
    }

    /**
     *
     * @return возвращает питомца
     */
    public Pet getPet() {
        return this.pet;
    }

    /**
     *
     * @return возвращает клиента по идентификатору
     */
    public int getId() {
        return this.id;
    }

    /**
     *
     * @param id добавляет клиента по идентификатору
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     *
     * @return возвращает имя клиента
     */
    public String getName() {
        return name;
    }

    /**
     *
     * @param name добавляет имя клиента
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     *
     * @return возвращает строковое представление класса Client
     */
    @Override
    public String toString() {
        return "Client{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", pet=" + pet +
                '}';
    }
}
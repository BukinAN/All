package mvc.Clinic.models.clinic;

import mvc.Clinic.models.clinic.animals.Pet;


public class Client {
    private int id;
    private String name;
    private final Pet pet;

    /**
     *
     * @param id ������������� �������
     * @param name ��� �������
     * @param pet �������
     */
    public Client(int id,String name, Pet pet) {
        this.id = id;
        this.name = name;
        this.pet = pet;
    }

    /**
     *
     * @return ���������� �������
     */
    public Pet getPet() {
        return this.pet;
    }

    /**
     *
     * @return ���������� ������� �� ��������������
     */
    public int getId() {
        return this.id;
    }

    /**
     *
     * @param id ��������� ������� �� ��������������
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     *
     * @return ���������� ��� �������
     */
    public String getName() {
        return name;
    }

    /**
     *
     * @param name ��������� ��� �������
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     *
     * @return ���������� ��������� ������������� ������ Client
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
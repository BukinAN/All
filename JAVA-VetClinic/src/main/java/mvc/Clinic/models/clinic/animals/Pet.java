package mvc.Clinic.models.clinic.animals;


public abstract class Pet {

    protected String name;

    /**
     * �����������
     * @param name ��� �������
     */
    public Pet(String name) {
        this.name = name;
    }

    /**
     *
     * @param name ��� �������
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     *
     * @return ���������� ��� �������
     */
    public String getName() {
        return this.name;
    }

    /**
     *
     * @return ��������� ������������� ������ Pet
     */
    @Override
    public String toString() {
        return this.getClass().getSimpleName() + "{" +
                "name='" + name + '\'' +
                '}';
    }
}
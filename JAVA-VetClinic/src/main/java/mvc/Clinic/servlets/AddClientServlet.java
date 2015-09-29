package mvc.Clinic.servlets;

import mvc.Clinic.models.clinic.Client;
import mvc.Clinic.models.clinic.Clinic;
import mvc.Clinic.models.clinic.animals.Cat;
import mvc.Clinic.models.clinic.animals.Dog;
import mvc.Clinic.models.clinic.animals.Parrot;
import mvc.Clinic.models.clinic.animals.Pet;


import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.concurrent.atomic.AtomicInteger;

@WebServlet(name = "AddClientServlet", urlPatterns = "/add")
public class AddClientServlet extends HttpServlet {
    final AtomicInteger ids = new AtomicInteger();
    private Clinic clinic = Clinic.getInstance();

    /**
     *
     * @param request
     * @param response
     * @throws ServletException
     * @throws IOException
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Pet pet = null;
        if (request.getParameter("pets") != null) {
            if (request.getParameter("pets").equals("dog")) {
                pet = new Dog(request.getParameter("petName"));
            } else if (request.getParameter("pets").equals("cat")) {
                pet = new Cat(request.getParameter("petName"));
            } else if (request.getParameter("pets").equals("parrot")) {
                pet = new Parrot(request.getParameter("petName"));
            }
            if (!request.getParameter("clientName").isEmpty() && !request.getParameter("petName").isEmpty()) {
                this.clinic.addClient(new Client(ids.incrementAndGet(),request.getParameter("clientName"), pet));
            }
            request.setAttribute("clinic", clinic);
            RequestDispatcher dispatcher = request.getRequestDispatcher("/views/clinic/ClinicView.jsp");
            dispatcher.forward(request,response);

        }
    }

    /**
     *
     * @param request
     * @param response
     * @throws ServletException
     * @throws IOException
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }
}

package mvc.Clinic.servlets;

import mvc.Clinic.models.clinic.Clinic;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "DeleteClientServlet", urlPatterns = "/del")
public class DeleteClientServlet extends HttpServlet {
    private Clinic clinic = Clinic.getInstance();

    /**
     *
     * @param request
     * @param response
     * @throws ServletException
     * @throws IOException
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        clinic.removeClientByName(request.getParameter("clientNameDel"));
        request.setAttribute("clinic", clinic);
        RequestDispatcher dispatcher = request.getRequestDispatcher("/views/clinic/ClinicView.jsp");
        dispatcher.forward(request, response);

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

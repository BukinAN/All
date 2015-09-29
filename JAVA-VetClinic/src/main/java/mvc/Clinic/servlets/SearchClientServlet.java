package mvc.Clinic.servlets;

import mvc.Clinic.models.clinic.Clinic;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "SearchClientServlet", urlPatterns = "/search")
public class SearchClientServlet extends HttpServlet {
    private Clinic clinic = Clinic.getInstance();

    /**
     *
     * @param req
     * @param resp
     * @throws ServletException
     * @throws IOException
     */
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setAttribute("clients", clinic.findClient(req.getParameter("search")));

        RequestDispatcher dispatcher = req.getRequestDispatcher("/views/clinic/ClinicView.jsp");
        dispatcher.forward(req, resp);
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

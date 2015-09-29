<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
    <title>edit user</title>
</head>
<body>
<div class="edit_form">
    <form action="${pageContext.servletContext.contextPath}/edit" method='post'>
        <input type="hidden" name="id" value="${client.getId()}">
        Client's name : <input type='text' name='clientName' value="${client.getName()}">
        </br>
        </br>
        Pet's name : <input type='text' name='petName' value="${client.getPet().getName()}">
        </br>
        </br>
        <select name="pets">
            <option value="cat">Cat</option>
            <option value="dog">Dog</option>
            <option value="parrot">Parrot</option>
        </select>
        </br>
        </br>
        <input type='submit' value='Submit'>
        </br>
    </form>
    </br>

</div>

</table>


</body>
</html>

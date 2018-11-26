package com.ir.cs101.service;

import java.io.InputStream;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

import com.ir.cs101.core.impl.StringReverseFactory;
import com.ir.cs101.dto.StringReverseResponse;

@Path("/stringreverse/")
public class ReverseStringService {
  
  @GET
  @Path("/simple/{stringToReverse}")
  @Produces(MediaType.APPLICATION_JSON)
  public Response getSimpleReverseOfString(@PathParam("stringToReverse") String stringToReverse) {
    
    StringReverseResponse srr = new StringReverseResponse(stringToReverse, StringReverseFactory.GetSimpleStringReverse().reverse(stringToReverse));
    
    return Response.status(200).entity(srr).build();
  }
  
  @GET
  @Path("/recursive/{stringToReverse}")
  @Produces(MediaType.APPLICATION_JSON)
  public Response getRecursiveReverseOfString(@PathParam("stringToReverse") String stringToReverse) {
    
    StringReverseResponse srr = new StringReverseResponse(stringToReverse, StringReverseFactory.GetRecursiveStringReverse().reverse(stringToReverse));
    
    return Response.status(200).entity(srr).build();
  }
  
  @GET
  @Path("/loop/{stringToReverse}")
  @Produces(MediaType.APPLICATION_JSON)
  public Response getLoopAndTempReverseOfString(@PathParam("stringToReverse") String stringToReverse) {
    
    StringReverseResponse srr = new StringReverseResponse(stringToReverse, StringReverseFactory.GetLoopAndTempStringReverse().reverse(stringToReverse));
    
    return Response.status(200).entity(srr).build();
  }
  
  
  @GET
  @Path("/verify")
  @Produces(MediaType.TEXT_PLAIN)
  public Response verifyRESTService(InputStream incomingData) {
    String result = "ReverseStringService is running";
      return Response.status(200).entity(result).build();
  }
}

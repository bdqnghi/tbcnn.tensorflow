package darrenwrose.mergesort.web;

import darrenwrose.mergesort.model.Execution;
import darrenwrose.mergesort.service.MergesortService;
import io.swagger.annotations.ApiResponse;
import io.swagger.annotations.ApiResponses;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;

import java.util.List;

/**
 * Created by darrenrose on 18/11/2017.
 */
@RestController()
public class MergesortController {
    private static final Logger LOGGER = LoggerFactory.getLogger(MergesortController.class);

    private final MergesortService mergesortService;

    public MergesortController(MergesortService mergesortService) {
        this.mergesortService = mergesortService;
    }

    @ApiResponses(value = {
            @ApiResponse(code = 201, message = "The execution has been created", response = Execution.class),
            @ApiResponse(code = 400, message = "The request was invalid")
    })
    @ResponseStatus(HttpStatus.CREATED)
    @PostMapping(value = {"/mergesort", "/mergesort/executions"}, consumes = MediaType.APPLICATION_JSON_VALUE,produces = MediaType.APPLICATION_JSON_VALUE)
    public Execution mergesort(@RequestBody List<Integer> input){
        LOGGER.info("mergesort: {}", input);
        return mergesortService.mergesort(input);
    }

    @GetMapping(value = "/mergesort/executions", produces = MediaType.APPLICATION_JSON_VALUE)
    public List<Execution> executions(){
        LOGGER.info("executions");
        return mergesortService.executions();
    }

    @ApiResponses(value = {
            @ApiResponse(code = 200, message = "The execution", response = Execution.class),
            @ApiResponse(code = 400, message = "The execution id is invalid")
    })
    @ResponseStatus(HttpStatus.OK)
    @GetMapping(value = "/mergesort/executions/{id}", produces = MediaType.APPLICATION_JSON_VALUE)
    public Execution execution(@PathVariable("id") final int id){
        LOGGER.info("execution: {}", id);
        return mergesortService.execution(id);
    }

    @ApiResponses(value = {
            @ApiResponse(code = 200, message = "Delete all executions")
    })
    @DeleteMapping("/mergesort/executions")
    public void deleteAll(){
        LOGGER.info("delete all");
        mergesortService.deleteAll();
    }

    @ResponseStatus(HttpStatus.BAD_REQUEST)
    @ExceptionHandler(IllegalArgumentException.class)
    public void illegalArgumentException(IllegalArgumentException e){
        LOGGER.warn(e.toString());
    }

}

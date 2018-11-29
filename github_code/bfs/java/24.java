package wisc.academicadvisor;

import android.content.Intent;
import android.media.Rating;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RatingBar;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

public class CourseSearch extends AppCompatActivity {

    private String department, number, credits, professor, professorRating;
    private String url_S;
    private Spinner credit_spinner;
    private SeekBar avgGPA;
    private int filters = 0;
    private String gpa = "";

    @Override
    protected void onResume() {
        super.onResume();
        filters = 0;
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        filters = 0;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_course_search);

        // make it so editText doesn't pop up immediately
        this.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_ALWAYS_HIDDEN);

        credit_spinner = (Spinner) findViewById(R.id.credits_spinner);

        // all breadth options for spinnger (maybe add Ethnic Study (not a breadth option on course guide))
        String[] credits = new String[]
                {"---N/A---", "1", "2", "3", "4",
                        "5", "6", "7"};
        ArrayAdapter<String> adapterSpinner = new ArrayAdapter<String>(this,
                R.layout.spinner_item, credits);
        adapterSpinner.setDropDownViewResource(R.layout.spinner_dropdown);
        credit_spinner.setAdapter(adapterSpinner);

        avgGPA = (SeekBar) findViewById(R.id.gpa_seekBar);
        final TextView gpaTextDisplay = (TextView) findViewById(R.id.avgGPA_text);

        avgGPA.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                // TODO Auto-generated method stub
            }

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                gpa = String.format("%.02f", progress / 100.0);
                gpaTextDisplay.setText("Use Average GPA: " + gpa + " / 4.00");
            }

        });

    }

    public void launchURL(View v) {
        url_S = "http://tyleroconnell.com:8080/courses";
        boolean firstSearchParam = true;

        department = ((EditText) findViewById(R.id.dept_entry)).getText().toString().replace(" ", "%20");
        number = ((EditText) findViewById(R.id.courseNumberEdit)).getText().toString();
        credits = credit_spinner.getSelectedItem().toString().trim();
        professor = ((EditText) findViewById(R.id.profEntry)).getText().toString().replace(" ", "%20");

        if (department.length() > 0) {
            if (firstSearchParam) {
                url_S += "?";
                firstSearchParam = false;
            } else
                url_S += "&";
            url_S += "department=" + department;
            filters++;
        }
        if (number.length() > 0) {
            if (firstSearchParam) {
                url_S += "?";
                firstSearchParam = false;
            } else
                url_S += "&";
            url_S += "number=" + number;
            filters++;
        }
        if (credit_spinner.getSelectedItemPosition() != 0) {
            if (firstSearchParam) {
                url_S += "?";
                firstSearchParam = false;
            } else
                url_S += "&";
            url_S += "credits=" + credits;
            filters++;
        }
        if (professor.length() > 0) {
            if (firstSearchParam) {
                url_S += "?";
                firstSearchParam = false;
            } else
                url_S += "&";
            url_S += "professor=" + professor;
            filters++;
        }


        boolean firstBreadthReached = false;
        if (((CheckBox) findViewById(R.id.humanities)).isChecked()) {
            if (firstBreadthReached)
                url_S += "-";
            else {
                firstBreadthReached = true;
                if (firstSearchParam)
                    url_S += "?";
                else
                    url_S += "&";
                url_S += "breadth=";
            }
            url_S += "Humanities";
        }
        if (((CheckBox) findViewById(R.id.literature)).isChecked()) {
            if (firstBreadthReached)
                url_S += "-";
            else {
                firstBreadthReached = true;
                if (firstSearchParam)
                    url_S += "?";
                else
                    url_S += "&";
                url_S += "breadth=";
            }
            url_S += "Literature";
        }
        if (((CheckBox) findViewById(R.id.biological_sciences)).isChecked()) {
            if (firstBreadthReached)
                url_S += "-";
            else {
                firstBreadthReached = true;
                if (firstSearchParam)
                    url_S += "?";
                else
                    url_S += "&";
                url_S += "breadth=";
            }
            url_S += "Biological%20Science";
        }
        if (((CheckBox) findViewById(R.id.natural_science)).isChecked()) {
            if (firstBreadthReached)
                url_S += "-";
            else {
                firstBreadthReached = true;
                if (firstSearchParam)
                    url_S += "?";
                else
                    url_S += "&";
                url_S += "breadth=";
            }
            url_S += "Natural%20Science";
        }
        if (((CheckBox) findViewById(R.id.physical_science)).isChecked()) {
            if (firstBreadthReached)
                url_S += "-";
            else {
                firstBreadthReached = true;
                if (firstSearchParam)
                    url_S += "?";
                else
                    url_S += "&";
                url_S += "breadth=";
            }
            url_S += "Physical%20Science";
        }
        if (((CheckBox) findViewById(R.id.social_science)).isChecked()) {
            if (firstBreadthReached)
                url_S += "-";
            else {
                firstBreadthReached = true;
                if (firstSearchParam)
                    url_S += "?";
                else
                    url_S += "&";
                url_S += "breadth=";
            }
            url_S += "Social%20Science";
        }
        if (((CheckBox) findViewById(R.id.interdivisional)).isChecked()) {
            if (firstBreadthReached)
                url_S += "-";
            else {
                firstBreadthReached = true;
                if (firstSearchParam)
                    url_S += "?";
                else
                    url_S += "&";
                url_S += "breadth=";
            }
            url_S += "Interdivisional";
        }

        if (firstBreadthReached)
            filters++;

        Switch useProfRating = (Switch) findViewById(R.id.switch_profRating);
        Switch useAvgGPA = (Switch) findViewById(R.id.switch_GPA);
        professorRating = Double.toString(((RatingBar) findViewById(R.id.prof_rating_bar)).getRating());
        if (useProfRating.isChecked()) {
            if (firstSearchParam) {
                url_S += "?";
                firstSearchParam = false;
            } else
                url_S += "&";
            url_S += "rmp=" + professorRating;
            filters++;
        }

        if (useAvgGPA.isChecked()) {
            if (firstSearchParam) {
                url_S += "?";
                firstSearchParam = false;
            } else
                url_S += "&";
            url_S += "gpa=" + gpa;
            filters++;
        }

        String numFilters = filters + "";

        Toast.makeText(CourseSearch.this, filters + " filters selected", Toast.LENGTH_SHORT).show();


        Intent intent = new Intent(CourseSearch.this, CourseSearchResults.class);
        intent.putExtra("search_URL", url_S);
        intent.putExtra("filters", numFilters);
        startActivity(intent);
    }


}
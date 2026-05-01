package com.example.androidsample

import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.mapitron.Mapitron

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<TextView>(R.id.build_type).text = "build: ${Mapitron.buildType()}"

        val resultText = findViewById<TextView>(R.id.result)
        findViewById<Button>(R.id.button_add).setOnClickListener {
            resultText.text = "3 + 4 = ${Mapitron.add(3, 4)}"
        }
    }
}

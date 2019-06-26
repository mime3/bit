using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
	public partial class MainForm : System.Windows.Forms.Form
	{
		Random random = new Random(37);
		public MainForm()
		{
			InitializeComponent();
			lvDummy.Columns.Add("Name");
			lvDummy.Columns.Add("Depth");
		}
		void ChangeFont()
		{
			if (cboFont.SelectedIndex < 0)
				return;

			FontStyle style = FontStyle.Regular;

			if (chkBold.Checked)
				style |= FontStyle.Bold;
			if (chkItalic.Checked)
				style |= FontStyle.Italic;

			txtSampleText.Font = new Font((string)cboFont.SelectedItem, 10, style);

		}

		void TreeToList()
		{
			lvDummy.Items.Clear();
			foreach (TreeNode node in tvDummy.Nodes)
				TreeToList(node);
		}

		void TreeToList(TreeNode Node)
		{
			lvDummy.Items.Add(new ListViewItem(new string[] { Node.Text, Node.FullPath.Count(f => f == '\\').ToString() }));
			foreach (TreeNode node in Node.Nodes)
				TreeToList(node);
		}
			private void MainForm_Load(object sender, EventArgs e)
		{
			var Fonts = FontFamily.Families;
			foreach (FontFamily font in Fonts)
				cboFont.Items.Add(font.Name);
		}

		private void TbDummy_Scroll(object sender, EventArgs e)
		{
			pgDummy.Value = tbDummy.Value;
		}

		private void BtnModal_Click(object sender, EventArgs e)
		{
			Form frm = new Form();
			frm.Text = "Modal Form";
			frm.Width = 300;
			frm.Height = 100;
			frm.BackColor = Color.Red;
			frm.ShowDialog();
		}

		private void BtnModaless_Click(object sender, EventArgs e)
		{
			Form frm = new Form();
			frm.Text = "Modaless Form";
			frm.Width = 300;
			frm.Height = 300;
			frm.BackColor = Color.Green;
			frm.Show();
		}

		private void BtnMsgBox_Click(object sender, EventArgs e)
		{
			MessageBox.Show(txtSampleText.Text, "Message Box", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
		}
	}
}
